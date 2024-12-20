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
#include "xrefnode.h"

using namespace std;
using namespace node;

XREFNode::XREFNode() : m_trailerNode(nullptr)
{
}


void XREFNode::SetTrailer(const std::shared_ptr<TreeNode>& trailer)
{
    this->m_trailerNode = trailer;
}

std::shared_ptr<TreeNode> XREFNode::Trailer() const
{
    return m_trailerNode;
}

void XREFNode::AddNode(const uint16_t id, const uint16_t generation, const uint32_t address, const char status)
{
    ObjectReference xref{};
    xref.id = id;
    xref.generation = generation;
    xref.address = address;
    xref.status = status;
    m_references.push_back(xref);
}
