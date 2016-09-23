/*
 * PDF Tools.
 * Copyright (C) 2012-2016 Leonardo Alves da Costa
 * mailto:leonhad AT gmail DOT com
 *
 * SonarQube is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * SonarQube is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
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

