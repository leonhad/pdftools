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

ObjNode::ObjNode(int id, int generation) :
        TreeNode(), m_id(id), m_generation(generation), m_streamPos(istream::beg), m_value(nullptr)
{
}

ObjNode::~ObjNode()
{
    if (m_value)
    {
        delete m_value;
    }
}

int ObjNode::Id() const
{
    return m_id;
}

int ObjNode::Generation() const
{
    return m_generation;
}

TreeNode *ObjNode::Value() const
{
    return m_value;
}

bool ObjNode::SameObject(int i, int g) const
{
    return this->m_id == i && this->m_generation == g;
}

void ObjNode::SetValue(TreeNode *v)
{
    if (m_value)
    {
        delete m_value;
    }

    this->m_value = v;
}

void ObjNode::SetStreamPos(streampos pos)
{
    this->m_streamPos = pos;
}

streampos ObjNode::StreamPos() const
{
    return m_streamPos;
}
