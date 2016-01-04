#ifndef SCANNER_H
#define SCANNER_H

#include <istream>
#include <stdint.h>
#include "token.h"

class Scanner {
private:
    std::istream *m_filein;
    const char *m_error = nullptr;
    Token m_current;
    bool m_charset_conversion = true;

public:
    Scanner(std::istream *m_filein) noexcept;
    ~Scanner() = default;

    Token *next_token();
    bool good();
    const char *error();

    void ignore_line();
    size_t ignore_stream(int length);
    size_t pos();
    void to_pos(size_t pos);
    char *get_stream(int length);
    char *get_image_stream();
    void disable_charset_conversion();

    void clear() noexcept;
private:
    void unget_char();
    bool is_space(const char c);
    char next_char();
    TokenType reserved_lookup(const char *s);
};

#endif

