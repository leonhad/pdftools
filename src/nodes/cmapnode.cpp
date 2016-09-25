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
#include "cmapnode.h"
#include "codespacenode.h"
#include "charnode.h"

using namespace std;
using namespace node;

CMapNode::CMapNode() : TreeNode(), m_codespace(nullptr)
{
}

CMapNode::~CMapNode()
{
    for (auto &i : m_charnodes)
    {
        delete i;
    }

    if (m_codespace)
    {
        delete m_codespace;
    }
}

void CMapNode::add(CharNode *node)
{
    m_charnodes.push_back(node);
}

void CMapNode::set_codespace(CodeSpaceNode *codespace)
{
    m_codespace = codespace;
}

CodeSpaceNode *CMapNode::code_space() const
{
    return m_codespace;
}

size_t CMapNode::nodes() const
{
    return m_charnodes.size();
}

CharNode *CMapNode::node(size_t index) const
{
    return m_charnodes.at(index);
}
