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

/**
 * Stores and control the graphics state.
 */
class GraphicState
{
private:
    /**
     * Stores the current font.
     */
    Font *m_font;

    /**
     * Stores the state list.
     */
    std::vector<State *> m_states;

    /**
     * Stores the current state.
     */
    State *m_currentState;

public:
    /**
     * Creates a new instance.
     */
    GraphicState();

    /**
     * Do not use copy constructor.
     *
     * @param obj the instance to copy.
     */
    GraphicState(const GraphicState &obj) = delete;

    /**
     * Destroy this instance.
     */
    ~GraphicState();

    /**
     * Pushes a state.
     */
    void Push();

    /**
     * Pops the last state.
     */
    void Pop();

    /**
     * Sets a text matrix.
     *
     * @param a the matrix value.
     * @param b the matrix value.
     * @param c the matrix value.
     * @param d the matrix value.
     * @param e the matrix value.
     * @param f the matrix value.
     */
    void SetTextMatrix(double a, double b, double c, double d, double e, double f);

    /**
     * Gets the current text font.
     *
     * @return the current text font.
     */
    double GetTextFont();

    /**
     * Gets the current font.
     *
     * @return the current font.
     */
    Font *GetFont();

    /**
     * Sets the current font.
     *
     * @param font the font to set.
     */
    void SetFont(Font *font);
};

#endif
