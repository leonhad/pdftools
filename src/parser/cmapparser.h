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
#pragma once

#include "genericparser.h"
#include <istream>

namespace node
{
    class TreeNode;
    class CMapNode;
    class CodeSpaceNode;
}

namespace parser
{
    /**
     * Parses a CMap.
     */
    class CMapParser : public GenericParser
    {
        /**
         * The CMap node root.
         */
        std::shared_ptr<node::CMapNode> m_root;

    public:
        /**
         * Creates a new instance.
         *
         * @param stream the CMap stream to read.
         */
        explicit CMapParser(std::istream* stream);

        /**
         * Destroy this instance.
         */
        ~CMapParser() = default;

        /**
         * Parses the CMap node.
         *
         * @return the CMap tree node.
         */
        std::shared_ptr<node::CMapNode> Parse();

    private:
        /**
         * Parses a BF char sequence.
         *
         * @param count the total chars to parse.
         */
        void BfCharSequence(int count);

        /**
         * Parses a BF rage sequence.
         *
         * @param count the total range to parse.
         */
        void BfRangeSequence(int count);

        /**
         * Gets the code space sequence.
         *
         * @return the code space sequence.
         */
        std::shared_ptr<node::CodeSpaceNode> CodeSpaceSequence();
    };
}
