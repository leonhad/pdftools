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

#include "treenode.h"
#include <vector>
#include <cstddef>
#include <memory>

namespace node
{
    /**
     * Stores a root node.
     */
    class RootNode : public TreeNode
    {
        /**
         * The list of childhood nodes.
         */
        std::vector<std::shared_ptr<TreeNode>> m_child;

    public:
        /**
         * Creates a new instance.
         */
        RootNode() = default;

        /**
         * Destroy this instance.
         */
        ~RootNode() override = default;

        /**
         * Adds a child to this node.
         *
         * @param child the child to add.
         */
        void AddChild(const std::shared_ptr<TreeNode>& child);

        /**
         * Gets a child by its index.
         *
         * @param index the index.
         * @return the child.
         */
        [[nodiscard]] std::shared_ptr<TreeNode> Get(size_t index) const;

        /**
         * The total of childhood.
         *
         * @return the total of childhood.
         */
        [[nodiscard]] size_t Size() const;
    };
}
