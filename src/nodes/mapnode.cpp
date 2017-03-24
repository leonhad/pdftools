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
#include <algorithm>
#include <stdexcept>
#include <vector>
#include "mapnode.h"

using namespace std;
using namespace node;

MapNode::MapNode() :
        TreeNode()
{
}

MapNode::~MapNode()
{
    for (auto &i : m_values)
    {
        delete i.second;
    }
}

TreeNode *MapNode::get(string name) const
{
    try
    {
        return m_values.at(name);
    } catch (out_of_range &)
    {
        return nullptr;
    }
}

vector<string> MapNode::names() const
{
    vector<string> names;
    names.reserve(m_values.size());
    for (const auto &p : m_values)
    {
        names.push_back(p.first);
    }

    return names;
}

map<string, TreeNode *> MapNode::values() const
{
    return m_values;
}

void MapNode::push(string name, TreeNode *value)
{
    m_values [name] = value;
}
