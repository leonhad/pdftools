#ifndef SCANNER_H
#define SCANNER_H

#include <istream>
#include <stdint.h>
#include "token.h"

namespace parser {

    class Scanner {
    private:
        std::istream *m_filein;
        Token m_current;
        bool m_charset_conversion = true;

    public:
        Scanner(std::istream *m_filein) noexcept;
        ~Scanner() = default;

        Token *next_token() noexcept;
        bool good() const noexcept;

        void ignore_line() noexcept;
        size_t ignore_stream(int length) noexcept;
        size_t pos() const noexcept;
        void to_pos(size_t pos) noexcept;
        char *get_stream(int length) noexcept;
        char *get_image_stream() noexcept;
        void disable_charset_conversion() noexcept;

        void clear() noexcept;
    private:
        void unget_char() noexcept;
        char next_char() noexcept;
        TokenType reserved_lookup(const char *s) noexcept;
    };

}

#endif

