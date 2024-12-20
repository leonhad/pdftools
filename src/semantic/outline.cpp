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

const string& Outline::Title()
{
    return m_title;
}

void Outline::SetLocation(const double x, const double y)
{
    this->m_x = x;
    this->m_y = y;
}

size_t Outline::Size() const
{
    return m_children.size();
}

std::shared_ptr<Outline> Outline::Child(const size_t index)
{
    return m_children[index];
}

void Outline::SetTitle(const string& title)
{
    this->m_title = title;
}

void Outline::AddChild(const std::shared_ptr<Outline>& child)
{
    this->m_children.push_back(child);
}

void Outline::SetDestination(const int id, const int generation)
{
    this->m_id = id;
    this->m_generation = generation;
}

int Outline::Id() const
{
    return m_id;
}

int Outline::Generation() const
{
    return m_generation;
}
