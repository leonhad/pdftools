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
#include "objnode.h"

using namespace std;
using namespace node;

ObjNode::ObjNode(int id, int generation) : TreeNode(), m_id(id), m_generation(generation),
                                           m_streamPos(istream::beg), m_value(nullptr)
{
}

ObjNode::~ObjNode()
{
    if (m_value)
    {
        delete m_value;
    }
}

int ObjNode::id() const
{
    return m_id;
}

int ObjNode::generation() const
{
    return m_generation;
}

TreeNode *ObjNode::value() const
{
    return m_value;
}

bool ObjNode::sameObject(int id, int generation) const
{
    return m_id == id && m_generation == generation;
}

void ObjNode::setValue(TreeNode *value)
{
    if (m_value)
    {
        delete m_value;
    }

    m_value = value;
}

void ObjNode::setStreamPos(istream::pos_type pos)
{
    m_streamPos = pos;
}

istream::pos_type ObjNode::streamPos() const
{
    return m_streamPos;
}
