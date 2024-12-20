/*
 * PDF Tools.
 * Copyright (C) 2012-2016 Leonardo Alves da Costa
 * mailto:leonhad AT gmail DOT com
 *
 * PDF Tools is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * PDF Tools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
#include "scanner.h"
#include "../utils.h"
#include <cstring>
#include <sstream>

using namespace std;
using namespace parser;

namespace parser
{
    constexpr auto special_chars = "\r\n<()/[]>";
    constexpr int HEX_BASE = 16;

    enum class StateType
    {
        START, INNUM, INNAME, INSTRING, INHEXSTR, DONE
    };

    struct reserved_words
    {
        TokenType type;
        const char* name;
    };

    const static reserved_words words[] =
    {
        {TokenType::OBJ, "obj"},
        {TokenType::END_OBJ, "endobj"},
        {TokenType::END_PDF, "EOF"},
        {TokenType::XREF, "xref"},
        {TokenType::TRUE, "true"},
        {TokenType::FALSE, "false"},
        {TokenType::STREAM, "stream"},
        {TokenType::END_STREAM, "endstream"},
        {TokenType::START_XREF, "startxref"},
        {TokenType::TRAILER, "trailer"},
        {TokenType::BT, "BT"},
        {TokenType::ET, "ET"},
        {TokenType::MP, "MP"},
        {TokenType::DP, "DP"},
        {TokenType::BMC, "BMC"},
        {TokenType::BDC, "BDC"},
        {TokenType::EMC, "EMC"},
        {TokenType::BX, "BX"},
        {TokenType::EX, "EX"},
        {TokenType::TJ_UP, "TJ"},
        {TokenType::TJ_LO, "Tj"},
        {TokenType::QUOTE, "'"},
        {TokenType::DOUBLE_QUOTE, "\""},
        {TokenType::GS, "gs"},
        {TokenType::TF, "Tf"},
        {TokenType::TW, "Tw"},
        {TokenType::TZ, "Tz"},
        {TokenType::TL, "TL"},
        {TokenType::T_AST, "T*"},
        {TokenType::TR, "Tr"},
        {TokenType::TS, "Ts"},
        {TokenType::TC, "Tc"},
        {TokenType::TM, "Tm"},
        {TokenType::D0, "d0"},
        {TokenType::D1, "d1"},
        {TokenType::SH, "sh"},
        {TokenType::N, "n"},
        {TokenType::TD_LO, "Td"},
        {TokenType::TD_UP, "TD"},
        {TokenType::SCN_UP, "SCN"},
        {TokenType::SCN_LO, "scn"},
        {TokenType::SC_UP, "SC"},
        {TokenType::SC_LO, "sc"},
        {TokenType::G_LO, "g"},
        {TokenType::G_UP, "G"},
        {TokenType::RE, "re"},
        {TokenType::RI, "ri"},
        {TokenType::CS_UP, "CS"},
        {TokenType::CS_LO, "cs"},
        {TokenType::W_LO, "w"},
        {TokenType::W_UP, "W"},
        {TokenType::W_AST, "W*"},
        {TokenType::Q_UP, "Q"},
        {TokenType::Q_LO, "q"},
        {TokenType::F_AST, "f*"},
        {TokenType::F_UP, "F"},
        {TokenType::F_LO, "f"},
        {TokenType::RG_UP, "RG"},
        {TokenType::RG_LO, "rg"},
        {TokenType::M_LO, "m"},
        {TokenType::M_UP, "M"},
        {TokenType::K_LO, "k"},
        {TokenType::K_UP, "K"},
        {TokenType::J_LO, "j"},
        {TokenType::J_UP, "J"},
        {TokenType::S_LO, "s"},
        {TokenType::S_UP, "S"},
        {TokenType::C, "c"},
        {TokenType::CM, "cm"},
        {TokenType::DO, "Do"},
        {TokenType::L, "l"},
        {TokenType::D, "d"},
        {TokenType::H, "h"},
        {TokenType::V, "v"},
        {TokenType::Y, "y"},
        {TokenType::I, "i"},
        {TokenType::BI, "BI"},
        {TokenType::ID, "ID"},
        {TokenType::B_UP, "B"},
        {TokenType::B_UP_AST, "B*"},
        {TokenType::B_LO, "b"},
        {TokenType::B_LO_AST, "b*"},
        {TokenType::EI, "EI"}
    };

    constexpr bool isnum(const char c)
    {
        return (c >= '0' && c <= '9') || (c == '-') || (c == '+') || (c == '.');
    }

    constexpr bool is_space(const char c)
    {
        return (c == '\0') || (c == ' ') || (c == '\t') || (c == '\n') || (c == '\v') || (c == '\f')
            || (c == '\r') || (c == EOF);
    }
}

Scanner::Scanner(istream* m_filein) :
    m_filein(m_filein), m_charset_conversion(true)
{
}

void Scanner::DisableCharsetConversion()
{
    m_charset_conversion = false;
}

streampos Scanner::Pos() const
{
    return m_filein->tellg();
}

void Scanner::Clear() const
{
    m_filein->clear();
}

void Scanner::ToPos(const streampos pos) const
{
    if (m_filein->good())
    {
        m_filein->seekg(pos, ios::beg);
    }
    else
    {
        ErrorMessage(L"Stream not good for use.");
    }
}

streampos Scanner::IgnoreStream(const int length) const
{
    // Ignore first new line
    while (m_filein->good() && NextChar() != '\n')
    {
    }

    const istream::pos_type ret = m_filein->tellg();

    if (length >= 0)
    {
        m_filein->ignore(length);
    }
    else
    {
        while (m_filein->good())
        {
            if (const int next = m_filein->get(); next == 'e' && m_filein->good())
            {
                // endstream buffer (ndstream + \0)
                char buff[9];
                const istream::pos_type pos = m_filein->tellg();

                memset(buff, 0, sizeof(buff));
                m_filein->read(buff, sizeof(buff) - 1);

                // restore state, need by the parser anyway
                m_filein->seekg(pos);

                if (strcmp("ndstream", buff) == 0)
                {
                    // restore the endstream token
                    m_filein->seekg((int)pos - 1);
                    break;
                }
            }
        }
    }
    return ret;
}

void Scanner::ImageStream() const
{
    // Ignore first new line
    while (m_filein->good() && NextChar() != '\n')
    {
    }

    UnGetChar();

    while (m_filein->good())
    {
        if (const int ret = m_filein->get(); (ret == '\n' || ret == '\r') && m_filein->good())
        {
            const istream::pos_type pos = m_filein->tellg();

            // treat '\r\n', '\r' or '\n'
            if (const int next = m_filein->get(); next == 'E' || m_filein->get() == 'I')
            {
                UnGetChar();
                UnGetChar();
                break;
            }

            // not the end of stream.
            m_filein->seekg(pos);
        }
    }
}

string Scanner::Stream(const streamsize length) const
{
    const auto stream = static_cast<char*>(alloca(static_cast<unsigned long>(length)));
    m_filein->read(stream, length);
    return stream;
}

char Scanner::NextChar() const
{
    int ret = EOF;

    if (m_filein->good() && not m_filein->eof())
    {
        ret = m_filein->get();
        if (ret == '\r')
        {
            int second = m_filein->get();
            if (second == '\n')
            {
                return '\n';
            }

            UnGetChar();
        }
    }
    return static_cast<char>(ret);
}

bool Scanner::Good() const
{
    return m_filein->good();
}

void Scanner::IgnoreLine()
{
    while (NextChar() != '\n')
    {
    }
}

void Scanner::UnGetChar() const
{
    m_filein->unget();
}

TokenType Scanner::ReservedLookup(const string& reserved_word)
{
    for (const auto [type, name] : words)
    {
        if (name == reserved_word)
        {
            return type;
        }
    }

    return TokenType::NAME;
}

Token& Scanner::NextToken()
{
    string token_string;
    auto current_token = TokenType::ENDFILE;
    auto state = StateType::START;
    int inner_string = 0;

    bool save;
    while (state != StateType::DONE && m_filein->good())
    {
        char c = NextChar();
        save = true;
        switch (state)
        {
        case StateType::START:
            if (isnum(c))
            {
                state = StateType::INNUM;
            }
            else if (c == '%')
            {
                current_token = TokenType::PERCENT;
                state = StateType::DONE;
            }
            else if (c == '[')
            {
                current_token = TokenType::START_ARRAY;
                state = StateType::DONE;
            }
            else if (c == ']')
            {
                current_token = TokenType::END_ARRAY;
                state = StateType::DONE;
            }
            else if (c == '>')
            {
                wchar_t next = NextChar();
                if (next != '>')
                {
                    UnGetChar();
                    save = false;
                    current_token = TokenType::ERROR;
                }
                else
                {
                    token_string += '>';
                    current_token = TokenType::END_DICT;
                }

                state = StateType::DONE;
            }
            else if (c == '(')
            {
                save = false;
                state = StateType::INSTRING;
            }
            else if (c == '<')
            {
                wchar_t next = NextChar();
                if (next != '<')
                {
                    UnGetChar();
                    save = false;
                    state = StateType::INHEXSTR;
                }
                else
                {
                    token_string += '<';
                    state = StateType::DONE;
                    current_token = TokenType::START_DICT;
                }
            }
            else if (is_space(c))
            {
                save = false;
            }
            else if (isalpha(c) || c == '/' || c == '\'' || c == '"')
            {
                state = StateType::INNAME;
            }
            else if (c == '\n' || c == '\r')
            {
                state = StateType::DONE;
                current_token = TokenType::NEW_LINE;
            }
            else if (c == EOF)
            {
                state = StateType::DONE;
                current_token = TokenType::ENDFILE;
            }
            else
            {
                wstring msg = L"Invalid char ";
                msg += c;
                ErrorMessage(msg);
                state = StateType::DONE;
                save = false;
                current_token = TokenType::ERROR;
            }

            break;
        case StateType::INNUM:
            if (not isdigit(c) && (c != '.'))
            {
                /* backup in the input */
                UnGetChar();
                save = false;
                state = StateType::DONE;
                current_token = TokenType::NUM;
            }

            break;
        case StateType::INHEXSTR:
            if (is_space(c))
            {
                save = false;
            }
            else if (c == '>')
            {
                save = false;
                state = StateType::DONE;

                string str;

                for (unsigned int loop = 0; loop < token_string.length(); loop += 2)
                {
                    str.push_back(static_cast<char>(stoi(token_string.substr(loop, 2), nullptr, HEX_BASE)));
                }

                if (m_charset_conversion)
                {
                    token_string = CharsetToUTF8(str);
                }
                else
                {
                    token_string = str;
                }
                current_token = TokenType::STRING;
            }

            break;
        case StateType::INSTRING:
            if (c == '(')
            {
                inner_string++;
            }
            else if (c == '\\')
            {
                // save the next char
                c = NextChar();
                if (c >= '0' && c <= '9')
                {
                    string value
                        {c};
                    value += NextChar();
                    char c3 = NextChar();
                    if (isnum(c3))
                    {
                        // for \99 only
                        value += c3;
                    }
                    c = static_cast<char>(stoi(value, nullptr, 8));
                }

                switch (c)
                {
                case 'n':
                    c = '\n';
                    break;
                case 'r':
                    c = '\r';
                    break;
                case 't':
                    c = '\t';
                    break;
                case 'b':
                    c = '\b';
                    break;
                case 'f':
                    c = '\f';
                    break;
                case '(':
                case ')':
                case '\\':
                    // keep the same char
                    break;
                case '\n':
                case '\r':
                default:
                    save = false;
                    break;
                }
            }
            else if (c == ')')
            {
                if (inner_string > 0)
                {
                    inner_string--;
                }
                else
                {
                    if (m_charset_conversion)
                    {
                        token_string = CharsetToUTF8(token_string);
                    }

                    save = false;
                    state = StateType::DONE;
                    current_token = TokenType::STRING;
                }
            }

            break;
        case StateType::INNAME:
            if (is_space(c) || strchr(special_chars, c))
            {
                save = false;
                UnGetChar();
                state = StateType::DONE;
                current_token = ReservedLookup(token_string);
            }

            break;
        default:
            break;
        }

        if (save)
        {
            token_string.push_back(c);
        }
    }

    m_current.SetType(current_token);
    m_current.SetValue(token_string);

    return m_current;
}
