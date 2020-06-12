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
        TreeNode(), id(id), generation(generation), streamPos(istream::beg), value(nullptr)
{
}

ObjNode::~ObjNode()
{
    if (value)
    {
        delete value;
    }
}

int ObjNode::Id() const
{
    return id;
}

int ObjNode::Generation() const
{
    return generation;
}

TreeNode *ObjNode::Value() const
{
    return value;
}

bool ObjNode::SameObject(int id, int generation) const
{
    return this->id == id && this->generation == generation;
}

void ObjNode::SetValue(TreeNode *value)
{
    if (value)
    {
        delete value;
    }

    this->value = value;
}

void ObjNode::SetStreamPos(istream::pos_type pos)
{
    this->streamPos = pos;
}

istream::pos_type ObjNode::StreamPos() const
{
    return streamPos;
}
