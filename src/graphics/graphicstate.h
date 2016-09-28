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
#ifndef GRAPHICSTATE_H
#define GRAPHICSTATE_H

#include <vector>

class Font;

class State;

class GraphicState
{
private:
    Font *m_font;
    std::vector<State *> m_states;
    State *m_current_state;

public:
    GraphicState();

    GraphicState(const GraphicState &obj) = delete;

    ~GraphicState();

    void push();

    void pop();

    void setTextMatrix(double a, double b, double c, double d, double e, double f);

    double getTextFont();

    Font *font();

    void setFont(Font *font);
};

#endif
