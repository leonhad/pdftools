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
#ifndef GENERICPARSER_H
#define GENERICPARSER_H

#include "scanner.h"
#include <sstream>

namespace node
{
    class TreeNode;
}

namespace parser
{
/**
 * The generic parser used in this project.
 */
class GenericParser
{
    protected:
        /**
         * The file scanner.
         */
        Scanner *m_scanner;

        /**
         * The current token.
         */
        Token *m_token;

    public:
        /**
         * Creates a new instance.
         *
         * @param filein the file to parse.
         */
        explicit GenericParser(std::istream *filein);

        /**
         * Destroy this instance.
         */
        ~GenericParser();

    protected:
        /**
         * Gets the tree node sequence value.
         *
         * @return the tree node sequence value.
         */
        node::TreeNode *ValueSequence();

        /**
         * Checks if the current token have the some type.
         *
         * @param type the type to check with the current token.
         * @return true if are the same.
         */
        bool Match(TokenType type);

        /**
         * Reads the next token.
         */
        void NextToken();
    };
}

#endif
