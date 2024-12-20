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
        explicit Scanner(std::istream *m_filein);

        /**
         * Destroy this instance.
         */
        ~Scanner() = default;

        /**
         * Reads the next token.
         *
         * @return the next token.
         */
        Token &NextToken();

        /**
         * If this scanner have more tokens.
         *
         * @return true if this scanner have more tokens.
         */
        [[nodiscard]] bool Good() const;

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
        [[nodiscard]] std::streampos IgnoreStream(int length) const;

        /**
         * Gets the current position.
         *
         * @return the current position.
         */
        [[nodiscard]] std::streampos Pos() const;

        /**
         * Change the current position.
         *
         * @param pos the position to switch.
         */
        void ToPos(std::streampos pos) const;

        /**
         * Gets a stream of bytes.
         *
         * @param length the length to read.
         * @return the stream.
         */
        [[nodiscard]] std::string Stream(std::streamsize length) const;

        /**
         * Handles an image stream.
         */
        void ImageStream() const;

        /**
         * Disable the charset conversion.
         */
        void DisableCharsetConversion();

        /**
         * Clears the file stream.
         */
        void Clear() const;

    private:
        /**
         * Returns a char to the buffer.
         */
        void UnGetChar() const;

        /**
         * Gets the next char.
         *
         * @return the next char.
         */
        [[nodiscard]] char NextChar() const;

        /**
         * Gets the token type by a string.
         *
         * @param reserved_word the string to lookup.
         * @return the token type by a string.
         */
        static TokenType ReservedLookup(const std::string& reserved_word);
    };
}

#endif
