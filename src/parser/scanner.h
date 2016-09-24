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
        bool m_charset_conversion;

    public:
        Scanner(std::istream *m_filein);
        ~Scanner() = default;

        Token *next_token();
        bool good() const;

        void ignore_line();
        size_t ignore_stream(int length);
        size_t pos() const;
        void to_pos(size_t pos);
        char *get_stream(int length);
        char *get_image_stream();
        void disable_charset_conversion();

        void clear();
    private:
        void unget_char();
        char next_char();
        TokenType reserved_lookup(const char *s);
    };

}

#endif

