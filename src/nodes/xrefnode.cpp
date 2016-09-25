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
#include "xrefnode.h"

using namespace std;
using namespace node;

XREFNode::XREFNode() : TreeNode()
{
}

XREFNode::~XREFNode()
{
    if (m_trailer)
    {
        delete m_trailer;
    }
}

void XREFNode::set_trailer(TreeNode *trailer)
{
    m_trailer = trailer;
}

TreeNode *XREFNode::trailer() const
{
    return m_trailer;
}

void XREFNode::add_node(uint16_t id, uint16_t generation, uint32_t address, char status)
{
    object_reference xref;
    xref.id = id;
    xref.generation = generation;
    xref.address = address;
    xref.status = status;
    m_references.push_back(xref);
}
