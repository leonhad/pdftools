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
#include "graphicstate.h"
#include "state.h"

using namespace std;

GraphicState::GraphicState() : m_font(nullptr), m_currentState(new State)
{
}

double GraphicState::GetTextFont() const
{
    return m_currentState->GetTextFont();
}

void GraphicState::SetTextMatrix(const double a, const double b, const double c, const double d, const double e, const double f) const
{
    m_currentState->SetTextMatrix(a, b, c, d, e, f);
}

void GraphicState::Push()
{
}

void GraphicState::Pop()
{
}

std::shared_ptr<Font> GraphicState::GetFont()
{
    return m_font;
}

void GraphicState::SetFont(const std::shared_ptr<Font>& font)
{
    this->m_font = font;
}
