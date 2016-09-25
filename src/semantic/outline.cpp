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
#include "outline.h"

Outline::Outline()
{
    m_id = 0;
    m_generation = 0;
    m_x = 0;
    m_y = 0;
}

Outline::~Outline()
{
    vector<Outline *>::iterator i = m_childs.begin();
    while (i != m_childs.end())
    {
        delete *i;
        i++;
    }
}

const char *Outline::title()
{
    return m_title.c_str();
}

void Outline::set_location(double x, double y)
{
    m_x = x;
    m_y = y;
}

size_t Outline::size()
{
    return m_childs.size();
}

Outline *Outline::child(size_t index)
{
    return m_childs[index];
}

void Outline::set_title(string title)
{
    m_title = title;
}

void Outline::add_child(Outline *child)
{
    m_childs.push_back(child);
}

void Outline::set_destination(int id, int generation)
{
    m_id = id;
    m_generation = generation;
}

int Outline::id()
{
    return m_id;
}

int Outline::generation()
{
    return m_generation;
}
