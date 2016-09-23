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
#include "bdcnode.h"

using namespace std;
using namespace node;

BDCNode::BDCNode(RootNode *parent) : RootNode()
{
    m_value = nullptr;
    m_parent = parent;
}

BDCNode::~BDCNode()
{
    if (m_value) {
        delete m_value;
    }
}

TreeNode *BDCNode::value()
{
    return m_value;
}

string BDCNode::name()
{
    return m_name;
}

void BDCNode::set_value(TreeNode *value)
{
    m_value = value;
}

void BDCNode::set_name(string name)
{
    m_name = name;
}

RootNode *BDCNode::parent()
{
    return m_parent;
}
