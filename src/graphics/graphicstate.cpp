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
#include "graphicstate.h"
#include "state.h"
#include <iostream>

using namespace std;

GraphicState::GraphicState()
{
    m_current_state = new State;
}

GraphicState::~GraphicState()
{
    if (m_current_state) delete m_current_state;
}

double GraphicState::get_text_font()
{
    return m_current_state->get_text_font();
}

void GraphicState::set_text_matrix(double a, double b, double c, double d, double e, double f)
{
    m_current_state->set_text_matrix(a, b, c, d, e, f);
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

void GraphicState::set_font(Font *font)
{
    m_font = font;
}
