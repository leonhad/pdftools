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
#pragma once

/**
 * Stores a current state.
 */
class State
{
    /**
     * The current text matrix.
     */
    double m_textMatrix[3][3]{};

public:
    /**
     * Creates a new instance.
     */
    State();

    /**
     * Destroy this instance.
     */
    ~State() = default;

    /**
     * Reset the current state.
     */
    void Reset();

    /**
     * Set the current text matrix.
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
    [[nodiscard]] double GetTextFont() const;
};
