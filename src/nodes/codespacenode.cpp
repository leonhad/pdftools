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
#include "codespacenode.h"

using namespace std;
using namespace node;

CodeSpaceNode::CodeSpaceNode() :
        TreeNode()
{
}

void CodeSpaceNode::setStart(const string &start)
{
    m_start = start;
}

void CodeSpaceNode::setFinish(const string &finish)
{
    m_finish = finish;
}

string CodeSpaceNode::start() const
{
    return m_start;
}

string CodeSpaceNode::finish() const
{
    return m_finish;
}
