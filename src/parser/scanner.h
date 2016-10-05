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
#ifndef SCANNER_H
#define SCANNER_H

#include <istream>
#include <stdint.h>
#include "token.h"

namespace parser
{
    /**
     * A generic scanner to read PDF files.
     */
    class Scanner
    {
    private:
        /**
         * A pointer to file input.
         */
        std::istream *m_filein;

        /**
         * The current token.
         */
        Token m_current;

        /**
         * If the scanner can do a charset conversion.
         */
        bool m_charset_conversion;

    public:
        /**
         * Create a new instance.
         *
         * @param m_filein the file to read.
         */
        Scanner(std::istream *m_filein);

        /**
         * Destroy this instance.
         */
        ~Scanner() = default;

        /**
         * Reads the next token.
         *
         * \return the next token.
         */
        Token *nextToken();

        /**
         * If this scanner have more tokens.
         *
         * \return true if this scanner have more tokens.
         */
        bool good() const;

        /**
         * Ignore a line.
         */
        void ignoreLine();

        /**
         * Ignore a stream of bytes by its length.
         *
         * \param length the length to ignore.
         * \return the size skipped.
         */
        std::istream::pos_type ignoreStream(int length);

        /**
         * Gets the current position.
         *
         * \return the current position.
         */
        std::istream::pos_type pos() const;

        /**
         * Change the current position.
         *
         * \param pos the position to switch.
         */
        void to_pos(std::istream::pos_type pos);

        /**
         * Gets a stream of bytes.
         *
         * \param length the length to read.
         * \return the stream.
         */
        char *getStream(int length);

        /**
         * Get a image stream.
         *
         * \return the image stream.
         */
        char *getImageStream();

        /**
         * Disable the charset conversion.
         */
        void disableCharsetConversion();

        /**
         * Clears the file stream.
         */
        void clear();

    private:
        /**
         * Retuns a char to the buffer.
         */
        void ungetChar();

        /**
         * Gets the next char.
         *
         * \return the next char.
         */
        char nextChar();

        /**
         * Gets the token type by a string.
         *
         * \param s the string to lookup.
         * \return the token type by a string.
         */
        TokenType reserved_lookup(const char *s);
    };
}

#endif
