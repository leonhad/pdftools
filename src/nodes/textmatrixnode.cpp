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
#include "textmatrixnode.h"

using namespace node;

TextMatrixNode::TextMatrixNode(double a, double b, double c, double d, double e, double f) noexcept : TreeNode()
{
    m_a = a;
    m_b = b;
    m_c = c;
    m_d = d;
    m_e = e;
    m_f = f;
}

double TextMatrixNode::a() const noexcept
{
    return m_a;
}

double TextMatrixNode::b() const noexcept
{
    return m_b;
}

double TextMatrixNode::c() const noexcept
{
    return m_c;
}

double TextMatrixNode::d() const noexcept
{
    return m_d;
}

double TextMatrixNode::e() const noexcept
{
    return m_e;
}

double TextMatrixNode::f() const noexcept
{
    return m_f;
}
