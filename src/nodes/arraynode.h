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
     * Stores a array node.
     */
    class ArrayNode final : public TreeNode
    {
        /**
         * The array values.
         */
        std::vector<std::shared_ptr<TreeNode>> m_values;

    public:
        /**
         * Creates a new instance.
         */
        ArrayNode() = default;

        /**
         * Destroy the instance.
         */
        ~ArrayNode() override = default;

        /**
         * Adds a value in this array.
         *
         * @param value the value to store of.
         */
        void Push(const std::shared_ptr<TreeNode>& value);

        /**
         * Gets the value by its index.
         *
         * @param index the index to search of.
         * @return the value by index.
         */
        [[nodiscard]] std::shared_ptr<TreeNode> Value(size_t index) const;

        /**
         * Gets this array size.
         *
         * @return the array size.
         */
        [[nodiscard]] size_t Size() const;
    };
}
