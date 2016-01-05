#include "scanner.h"
#include "../utils.h"
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <iostream>

using namespace std;

static const char *special_chars = "\r\n<()/[]>";

enum class StateType {
    START, INNUM, INNAME, INSTRING, INHEXSTR, DONE
};

struct reserved_words {
    TokenType type;
    const char *name;
};

const static reserved_words words[] = { { TokenType::OBJ, "obj" }, { TokenType::END_OBJ, "endobj" },
    { TokenType::END_PDF, "EOF" }, { TokenType::XREF, "xref" }, { TokenType::TRUE, "true" }, { TokenType::FALSE, "false" },
    { TokenType::STREAM, "stream" }, { TokenType::END_STREAM, "endstream" }, { TokenType::START_XREF, "startxref" },
    { TokenType::TRAILER, "trailer" }, { TokenType::BT, "BT" }, { TokenType::ET, "ET" }, { TokenType::MP, "MP" }, { TokenType::DP, "DP" },
    { TokenType::BMC, "BMC" }, { TokenType::BDC, "BDC" }, { TokenType::EMC, "EMC" }, { TokenType::BX, "BX" }, { TokenType::EX, "EX" },
    { TokenType::TJ_UP, "TJ" }, { TokenType::TJ_LO, "Tj" }, { TokenType::QUOTE, "'" }, { TokenType::DOUBLE_QUOTE, "\"" },
    { TokenType::GS, "gs" }, { TokenType::TF, "Tf" }, { TokenType::TW, "Tw" }, { TokenType::TZ, "Tz" }, { TokenType::TL, "TL" },
    { TokenType::T_AST, "T*" }, { TokenType::TR, "Tr" }, { TokenType::TS, "Ts" }, { TokenType::TC, "Tc" }, { TokenType::TM, "Tm" },
    { TokenType::D0, "d0" }, { TokenType::D1, "d1" }, { TokenType::SH, "sh" }, { TokenType::N, "n" }, { TokenType::TD_LO, "Td" },
    { TokenType::TD_UP, "TD" }, { TokenType::SCN_UP, "SCN" }, { TokenType::SCN_LO, "scn" }, { TokenType::SC_UP, "SC" },
    { TokenType::SC_LO, "sc" }, { TokenType::G_LO, "g" }, { TokenType::G_UP, "G" }, { TokenType::RE, "re" }, { TokenType::RI, "ri" },
    { TokenType::CS_UP, "CS" }, { TokenType::CS_LO, "cs" }, { TokenType::W_LO, "w" }, { TokenType::W_UP, "W" }, { TokenType::W_AST, "W*" },
    { TokenType::Q_UP, "Q" }, { TokenType::Q_LO, "q" }, { TokenType::F_AST, "f*" }, { TokenType::F_UP, "F" }, { TokenType::F_LO, "f" },
    { TokenType::RG_UP, "RG" }, { TokenType::RG_LO, "rg" }, { TokenType::M_LO, "m" }, { TokenType::M_UP, "M" }, { TokenType::K_LO, "k" },
    { TokenType::K_UP, "K" }, { TokenType::J_LO, "j" }, { TokenType::J_UP, "J" }, { TokenType::S_LO, "s" }, { TokenType::S_UP, "S" },
    { TokenType::C, "c" }, { TokenType::CM, "cm" }, { TokenType::DO, "Do" }, { TokenType::L, "l" }, { TokenType::D, "d" }, { TokenType::H, "h" },
    { TokenType::V, "v" }, { TokenType::Y, "y" }, { TokenType::I, "i" }, { TokenType::BI, "BI" }, { TokenType::ID, "ID" }, { TokenType::B_UP, "B" },
    { TokenType::B_UP_AST, "B*" }, { TokenType::B_LO, "b" }, { TokenType::B_LO_AST, "b*" }, { TokenType::EI, "EI" } };

constexpr bool isnum(const char c) noexcept
{
    return (c >= '0' && c <= '9') || (c == '-') || (c == '+') || (c == '.');
}

constexpr unsigned int xtod(const char c) noexcept
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    return 0; // not a hex digit
}

constexpr bool is_space(const char c) noexcept
{
    return isspace(c) || (c == EOF);
}

Scanner::Scanner(istream *m_filein) noexcept : m_filein{m_filein}
{
}

void Scanner::disable_charset_conversion()
{
    m_charset_conversion = false;
}

size_t Scanner::pos()
{
    return m_filein->tellg();
}

void Scanner::clear() noexcept
{
    m_filein->clear();
}

void Scanner::to_pos(size_t pos)
{
#ifdef DEBUG
    ifstream *stream = dynamic_cast<ifstream *>(m_filein);
    if (stream && !stream->is_open()) {
        error_message("Stream not open!");
    }
#endif
    if (m_filein->good()) {
        m_filein->seekg(pos, ios::beg);
    } else {
        error_message("Stream not good for use.");
    }
}

size_t Scanner::ignore_stream(int length)
{
    // endstream buffer (ndstream + \0)
    char buff[9];

    // Ignore first new line
    while (m_filein->good() && next_char() != '\n') {
    }
    size_t ret = m_filein->tellg();

    if (length >= 0) {
        m_filein->ignore(length);
    } else {
        while (m_filein->good()) {
            char next = m_filein->get();
            if (next == 'e' && m_filein->good()) {
                size_t pos = m_filein->tellg();
                memset(buff, 0, sizeof(buff));
                m_filein->read(buff, sizeof(buff) - 1);

                // restore state, need by the parser anyway
                m_filein->seekg(pos);

                if (strcmp("ndstream", buff) == 0) {
                    // restore the endstrea token
                    unget_char();
                    break;
                }
                // not the endstream
            }
        }
    }
    return ret;
}

char *Scanner::get_image_stream()
{
    // Ignore first new line
    while (m_filein->good() && next_char() != '\n') {
    }
    unget_char();

    while (m_filein->good()) {
        int ret = m_filein->get();
        if ((ret == '\n' || ret == '\r') && m_filein->good()) {
            size_t pos = m_filein->tellg();
            int next = m_filein->get();
            // treat '\r\n', '\r' or '\n'
            if (next == 'E' || m_filein->get() == 'I') {
                m_filein->unget();
                m_filein->unget();
                break;
            }
            // not endstream
            m_filein->seekg(pos);
        }
    }
    // FIXME save image stream
    return nullptr;
}

char *Scanner::get_stream(int length)
{
    char *stream = new char[length];
    m_filein->read((char *) stream, length);
    return stream;
}

char Scanner::next_char()
{
    char ret = EOF;

    if (m_filein->good() && !m_filein->eof()) {
        ret = m_filein->get();
        if (ret == '\r') {
            char second = m_filein->get();
            if (second == '\n') {
                return '\n';
            }
            m_filein->unget();
        }
    }
    return ret;
}

bool Scanner::good()
{
    return m_filein->good();
}

void Scanner::ignore_line()
{
    while (next_char() != '\n')
        ;
    unget_char();
}

const char *Scanner::error()
{
    return m_error;
}

void Scanner::unget_char()
{
    m_filein->unget();
}

TokenType Scanner::reserved_lookup(const char *s)
{
    int size = sizeof(words) / sizeof(reserved_words);
    for (int i = 0; i < size; i++) {
        if (!strcmp(words[i].name, s)) {
            return words[i].type;
        }
    }
    return TokenType::NAME;
}

Token *Scanner::next_token()
{
    string token_string;
    TokenType current_token{TokenType::ENDFILE};
    StateType state{StateType::START};
    int inner_string{0};
    m_error = nullptr;

    bool save;
    while (state != StateType::DONE && m_filein->good()) {
        char c = next_char();
        save = true;
        switch (state) {
        case StateType::START:
            if (isnum(c)) {
                state = StateType::INNUM;
            } else if (c == '%') {
                current_token = TokenType::PERCENT;
                state = StateType::DONE;
            } else if (c == '[') {
                current_token = TokenType::START_ARRAY;
                state = StateType::DONE;
            } else if (c == ']') {
                current_token = TokenType::END_ARRAY;
                state = StateType::DONE;
            } else if (c == '>') {
                wchar_t next = next_char();
                if (next != '>') {
                    unget_char();
                    save = false;
                    current_token = TokenType::ERROR;
                } else {
                    token_string += '>';
                    current_token = TokenType::END_DICT;
                }
                state = StateType::DONE;
            } else if (c == '(') {
                save = false;
                state = StateType::INSTRING;
            } else if (c == '<') {
                wchar_t next = next_char();
                if (next != '<') {
                    unget_char();
                    save = false;
                    state = StateType::INHEXSTR;
                } else {
                    token_string += '<';
                    state = StateType::DONE;
                    current_token = TokenType::START_DICT;
                }
            } else if (is_space(c)) {
                save = false;
            } else if (isalpha(c) || c == '/' || c == '\'' || c == '"') {
                state = StateType::INNAME;
            } else if (c == '\n' || c == '\r') {
                state = StateType::DONE;
                current_token = TokenType::NEW_LINE;
            } else if (c == EOF) {
                state = StateType::DONE;
                current_token = TokenType::ENDFILE;
            } else {
                string msg = "Invalid char ";
                msg += c;
                error_message(msg.c_str());
                state = StateType::DONE;
                save = false;
                current_token = TokenType::ERROR;
            }
            break;
        case StateType::INNUM:
            if (!isdigit(c) && (c != '.')) {
                /* backup in the input */
                unget_char();
                save = false;
                state = StateType::DONE;
                current_token = TokenType::NUM;
            }
            break;
        case StateType::INHEXSTR:
            if (is_space(c)) {
                save = false;
            } else if (c == '>') {
                save = false;
                state = StateType::DONE;

                unsigned int loop;
                string str;

                // FIXME review this
                for (loop = 0; loop < token_string.length(); loop++) {
                    unsigned int h = xtod(token_string.at(loop)) << 4;
                    unsigned int l = 0;
                    loop++;
                    if (loop < token_string.length()) {
                        l = xtod(token_string.at(loop));
                    }
                    str.push_back(h + l);
                }
                if (m_charset_conversion) {
                    token_string = charset_to_utf8(str);
                } else {
                    token_string = str;
                }
                current_token = TokenType::STRING;
            }
            break;
        case StateType::INSTRING:
            if (c == '(') {
                inner_string++;
            } else if (c == '\\') {
                // save the next char
                c = next_char();
                if (c == '\n' || c == '\r') {
                    save = false;
                }
            } else if (c == ')') {
                if (inner_string > 0) {
                    inner_string--;
                } else {
                    if (m_charset_conversion) {
                        token_string = charset_to_utf8(token_string);
                    }
                    save = false;
                    state = StateType::DONE;
                    current_token = TokenType::STRING;
                }
            }
            break;
        case StateType::INNAME:
            if (is_space(c) || strchr(special_chars, c)) {
                save = false;
                unget_char();
                state = StateType::DONE;
                current_token = reserved_lookup(token_string.c_str());
            }
            break;
        case StateType::DONE:
            break;
        default:
            /* should never happen */
            error_message("Invalid scanner state");
            state = StateType::DONE;
            current_token = TokenType::ERROR;
            break;
        }
        if (save) {
            token_string.push_back(c);
        }
    }
    m_current.set_type(current_token);
    m_current.set_value(token_string);

    return &m_current;
}
