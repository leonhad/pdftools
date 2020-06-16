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
         * @return the next token.
         */
        Token *NextToken();

        /**
         * If this scanner have more tokens.
         *
         * @return true if this scanner have more tokens.
         */
        bool Good() const;

        /**
         * Ignore a line.
         */
        void IgnoreLine();

        /**
         * Ignore a stream of bytes by its length.
         *
         * @param length the length to ignore.
         * @return the size skipped.
         */
        std::streampos IgnoreStream(int length);

        /**
         * Gets the current position.
         *
         * @return the current position.
         */
        std::streampos Pos() const;

        /**
         * Change the current position.
         *
         * @param pos the position to switch.
         */
        void ToPos(std::streampos pos);

        /**
         * Gets a stream of bytes.
         *
         * @param length the length to read.
         * @return the stream.
         */
        char *Stream(std::streamsize length);

        /**
         * Get a image stream.
         *
         * @return the image stream.
         */
        char *ImageStream();

        /**
         * Disable the charset conversion.
         */
        void DisableCharsetConversion();

        /**
         * Clears the file stream.
         */
        void Clear();

    private:
        /**
         * Retuns a char to the buffer.
         */
        void UngetChar();

        /**
         * Gets the next char.
         *
         * @return the next char.
         */
        char NextChar();

        /**
         * Gets the token type by a string.
         *
         * @param s the string to lookup.
         * @return the token type by a string.
         */
        TokenType ReservedLookup(const char *s);
    };
}

#endif
