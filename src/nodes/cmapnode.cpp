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
#include "cmapnode.h"
#include "codespacenode.h"
#include "charnode.h"

using namespace std;
using namespace node;

CMapNode::CMapNode() : m_code_space(nullptr)
{
}

void CMapNode::Add(const std::shared_ptr<CharNode>& node)
{
    m_char_nodes.push_back(node);
}

void CMapNode::SetCodeSpace(const std::shared_ptr<CodeSpaceNode>& code_space)
{
    this->m_code_space = code_space;
}

std::shared_ptr<CodeSpaceNode> CMapNode::CodeSpace() const
{
    return m_code_space;
}

size_t CMapNode::Nodes() const
{
    return m_char_nodes.size();
}

std::shared_ptr<CharNode> CMapNode::Node(const size_t index) const
{
    return m_char_nodes.at(index);
}
