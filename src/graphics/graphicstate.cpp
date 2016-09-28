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
#include <iostream>

using namespace std;

GraphicState::GraphicState() : m_font(nullptr), m_current_state(new State)
{
}

GraphicState::~GraphicState()
{
    if (m_current_state)
    {
        delete m_current_state;
    }
}

double GraphicState::getTextFont()
{
    return m_current_state->getTextFont();
}

void GraphicState::setTextMatrix(double a, double b, double c, double d, double e, double f)
{
    m_current_state->setTextMatrix(a, b, c, d, e, f);
}

void GraphicState::push()
{
}

void GraphicState::pop()
{
}

Font *GraphicState::font()
{
    return m_font;
}

void GraphicState::setFont(Font *font)
{
    m_font = font;
}
