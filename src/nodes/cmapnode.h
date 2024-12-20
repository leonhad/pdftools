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

#include <memory>

#include "treenode.h"
#include <vector>

namespace node
{
    class CodeSpaceNode;

    class CharNode;

    /**
     * Stores a CMap node.
     */
    class CMapNode final : public TreeNode
    {
    private:
        /**
         * Stores a char node list.
         */
        std::vector<std::shared_ptr<CharNode>> m_char_nodes;

        /**
         * This node code space value.
         */
        std::shared_ptr<CodeSpaceNode> m_code_space;

    public:
        /**
         * Creates a new instance.
         */
        CMapNode();

        /**
         * Destroy this instance.
         */
        ~CMapNode() override = default;

        /**
         * Adds a char node.
         * @param node the char node to add.
         */
        void Add(const std::shared_ptr<CharNode>& node);

        /**
         * Sets the code space.
         *
         * @param code_space the code space to set.
         */
        void SetCodeSpace(const std::shared_ptr<CodeSpaceNode>& code_space);

        /**
         * Gets the code space.
         *
         * @return the code space.
         */
        [[nodiscard]] std::shared_ptr<CodeSpaceNode> CodeSpace() const;

        /**
         * Gets the total of childhood char nodes.
         *
         * @return the total of childhood char nodes.
         */
        [[nodiscard]] size_t Nodes() const;

        /**
         * Gets a char node by its index.
         *
         * @param index the char node index.
         * @return the char node.
         */
        [[nodiscard]] std::shared_ptr<CharNode> Node(size_t index) const;
    };
}

#endif
