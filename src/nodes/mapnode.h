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
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace node
{
    /**
     * Stores a map node.
     */
    class MapNode final : public TreeNode
    {
        /**
         * Stores a map of nodes.
         */
        std::map<std::string, std::shared_ptr<TreeNode>> m_values;

    public:
        /**
         * Creates a new instance.
         */
        MapNode() = default;

        /**
         * Destroy this instance.
         */
        ~MapNode() override = default;

        /**
         * Pushes a value to this map.
         *
         * @param name the node name.
         * @param value the node value.
         */
        void Put(const std::string& name, const std::shared_ptr<TreeNode>& value);

        /**
         * Gets the node names.
         *
         * @return the node names.
         */
        [[nodiscard]] std::vector<std::string> Names() const;

        /**
         * Gets a map by its name.
         *
         * @param name the node name.
         * @return the node.
         */
        [[nodiscard]] std::shared_ptr<TreeNode> Get(const std::string& name) const;
    };
}
