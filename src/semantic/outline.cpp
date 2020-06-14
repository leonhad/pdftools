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
#include "outline.h"

using namespace std;

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

const char *Outline::Title()
{
    return m_title.c_str();
}

void Outline::SetLocation(double newX, double newY)
{
    this->m_x = newX;
    this->m_y = newY;
}

size_t Outline::Size()
{
    return m_childs.size();
}

Outline *Outline::Child(size_t index)
{
    return m_childs [index];
}

void Outline::SetTitle(string t)
{
    this->m_title = t;
}

void Outline::AddChild(Outline *child)
{
    this->m_childs.push_back(child);
}

void Outline::SetDestination(int i, int g)
{
    this->m_id = i;
    this->m_generation = g;
}

int Outline::Id()
{
    return m_id;
}

int Outline::Generation()
{
    return m_generation;
}
