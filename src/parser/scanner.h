#ifndef SCANNER_H
#define SCANNER_H

#include <istream>
#include <stdint.h>
#include "token.h"

using namespace std;

class Scanner {
private:
    istream *m_filein;
    const char *m_error = nullptr;
    Token m_current;
    bool m_charset_conversion = true;

public:
    Scanner() = default;
    ~Scanner() = default;

    Token *next_token();
    void set_istream(istream *stream);
    istream *get_istream();
    bool good();
    const char *error();

    void ignore_line();
    size_t ignore_stream(int length);
    size_t pos();
    void to_pos(size_t pos);
    char *get_stream(int length);
    char *get_image_stream();
    void disable_charset_conversion();

private:
    void unget_char();
    bool is_space(const char c);
    char next_char();
    TokenType reserved_lookup(const char *s);
};

#endif

