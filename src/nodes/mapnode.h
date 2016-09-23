/*
 * PDF Tools.
 * Copyright (C) 2012-2016 Leonardo Alves da Costa
 * mailto:leonhad AT gmail DOT com
 *
 * SonarQube is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * SonarQube is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
#ifndef MAPNODE_H
#define MAPNODE_H

#include "treenode.h"
#include <map>
#include <string>
#include <vector>

namespace node {

    class MapNode : public TreeNode {
    private:
        std::map<std::string, TreeNode *> m_values;

    public:
        MapNode() noexcept;
        virtual ~MapNode() noexcept;

        void push(std::string name, TreeNode *value) noexcept;
        std::map<std::string, TreeNode *> values() const noexcept;
        std::vector<std::string> names() const noexcept;

        TreeNode *get(std::string name) const noexcept;
    };

}

#endif
