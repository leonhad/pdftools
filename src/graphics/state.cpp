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
#include "state.h"

State::State()
{
    reset();
}

double State::getTextFont() const
{
    return m_text_matrix[1][1];
}

void State::setTextMatrix(double a, double b, double c, double d, double e, double f)
{
    m_text_matrix[0][0] = a;
    m_text_matrix[0][1] = b;
    m_text_matrix[1][0] = c;
    m_text_matrix[1][1] = d;
    m_text_matrix[2][0] = e;
    m_text_matrix[2][1] = f;
}

void State::reset()
{
    m_text_matrix[0][0] = 1;
    m_text_matrix[0][1] = 0;
    m_text_matrix[0][2] = 0;
    m_text_matrix[1][0] = 0;
    m_text_matrix[1][1] = 1;
    m_text_matrix[1][2] = 0;
    m_text_matrix[2][0] = 0;
    m_text_matrix[2][1] = 0;
    m_text_matrix[2][2] = 1;
}
