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
#ifndef CMAPNODE_H
#define CMAPNODE_H

#include "treenode.h"
#include <vector>
#include <cstring>

namespace node
{
    class CodeSpaceNode;

    class CharNode;

    /**
     * Stores a CMap node.
     */
    class CMapNode: public TreeNode
    {
    private:
        /**
         * Stores a char node list.
         */
        std::vector<CharNode *> charnodes;

        /**
         * This node code space value.
         */
        CodeSpaceNode *codespace;

    public:
        /**
         * Creates a new instance.
         */
        CMapNode();

        /**
         * Destroy this instance.
         */
        virtual ~CMapNode();

        /**
         * Adds a char node.
         * @param node the char node to add.
         */
        void Add(CharNode *node);

        /**
         * Sets the code space.
         *
         * @param codespace the code space to set.
         */
        void SetCodespace(CodeSpaceNode *codespace);

        /**
         * Gets the code space.
         *
         * @return the code space.
         */
        CodeSpaceNode *CodeSpace() const;

        /**
         * Gets the total of childhood char nodes.
         *
         * @return the total of childhood char nodes.
         */
        size_t Nodes() const;

        /**
         * Gets a char node by its index.
         *
         * @param index the char node index.
         * @return the char node.
         */
        CharNode *Node(size_t index) const;
    };
}

#endif
