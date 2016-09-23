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
#include "objnode.h"
#include <cstdlib>

using namespace std;
using namespace node;

ObjNode::ObjNode(int id, int generation) noexcept : TreeNode(), m_id{id}, m_generation{generation}
{
}

ObjNode::~ObjNode() noexcept
{
    if (m_value) {
        delete m_value;
    }
}

int ObjNode::id() const noexcept
{
    return m_id;
}

int ObjNode::generation() const noexcept
{
    return m_generation;
}

TreeNode *ObjNode::value() const noexcept
{
    return m_value;
}

bool ObjNode::this_object(int id, int generation) const noexcept
{
    return m_id == id && m_generation == generation;
}

void ObjNode::set_value(TreeNode *value) noexcept
{
    if (m_value) {
        delete m_value;
    }
    m_value = value;
}

void ObjNode::set_stream_pos(size_t pos) noexcept
{
    m_stream_pos = pos;
}

size_t ObjNode::stream_pos() const noexcept
{
    return m_stream_pos;
}
