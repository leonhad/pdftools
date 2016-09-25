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
#include "arraynode.h"

using namespace std;
using namespace node;

ArrayNode::ArrayNode() : TreeNode()
{
}

ArrayNode::~ArrayNode()
{
    for (auto &i : m_values)
    {
        delete i;
    }
}

TreeNode *ArrayNode::value(size_t index) const
{
    return m_values[index];
}

size_t ArrayNode::size() const
{
    return m_values.size();
}

void ArrayNode::push(TreeNode *value)
{
    m_values.push_back(value);
}
