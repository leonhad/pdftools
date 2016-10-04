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
#ifndef TOKEN_H
#define TOKEN_H

#include <string>

namespace parser
{

    enum class TokenType
    {
        ENDFILE, ERROR, START_ARRAY, END_ARRAY, TRUE, FALSE,
        NAME, NUM, STRING, PERCENT, START_DICT, END_DICT, NEW_LINE,

        OBJ, END_OBJ, END_PDF, XREF, TRAILER, START_XREF, STREAM, END_STREAM,

        // Graphics state
                W_LO, J_LO, J_UP, M_UP, D, RI, I, GS,

        // Path painting
                S_UP, S_LO, F_UP, F_LO, F_AST, B_UP, B_UP_AST, B_LO, B_LO_AST, N,

        // Special Graphics state
                Q_UP, Q_LO, CM, V, Y,

        // Path construction
                M_LO, L, C, H, RE,

        // Clipping paths
                W_AST, W_UP,

        // Text objects
                BT, ET,

        // Text state
                TC, TW, TZ, TL, TF, TR, TS,

        // Text positioning
                TD_UP, TD_LO, TM, T_AST,

        // Text showing
                TJ_UP, TJ_LO, QUOTE, DOUBLE_QUOTE,

        // Type 3 fonts
                D0, D1,

        // Color
                CS_UP, CS_LO, SCN_UP, SCN_LO, SC_UP, SC_LO, G_LO, G_UP, RG_LO, RG_UP, K_LO, K_UP,

        // Shading patterns
                SH,

        // Inline images
                BI, ID, EI,

        // XObjects
                DO,

        // Marked content
                MP, DP, BMC, BDC, EMC,

        // Compatibility
                BX, EX
    };

    /**
     * Stores a single token.
     */
    class Token
    {
    private:
        /**
         * The token type.
         */
        TokenType m_type = TokenType::ENDFILE;

        /**
         * the token value.
         */
        std::string m_value;

    public:
        /**
         * Creates a new instance.
         */
        Token() = default;

        /**
         * Destroy this instance.
         */
        ~Token() = default;

        /**
         * Sets the token value.
         *
         * \param value the token value.
         */
        void setValue(std::string value);

        /**
         * Sets the token type.
         *
         * \param type the token type.
         */
        void setType(TokenType type);

        /**
         * Converts the token value to number.
         *
         * \return the number value.
         */
        double toNumber() const;

        /**
         * Gets the token value.
         *
         * \return the token value.
         */
        std::string value() const;

        /**
         * Gets the token type.
         *
         * \return the token type.
         */
        TokenType type() const;
    };
}

#endif
