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
    id = 0;
    generation = 0;
    x = 0;
    y = 0;
}

Outline::~Outline()
{
    vector<Outline *>::iterator i = childs.begin();
    while (i != childs.end())
    {
        delete *i;
        i++;
    }
}

const char *Outline::Title()
{
    return title.c_str();
}

void Outline::SetLocation(double newX, double newY)
{
    this->x = newX;
    this->y = newY;
}

size_t Outline::Size()
{
    return childs.size();
}

Outline *Outline::Child(size_t index)
{
    return childs [index];
}

void Outline::SetTitle(string t)
{
    this->title = t;
}

void Outline::AddChild(Outline *child)
{
    this->childs.push_back(child);
}

void Outline::SetDestination(int i, int g)
{
    this->id = i;
    this->generation = g;
}

int Outline::Id()
{
    return id;
}

int Outline::Generation()
{
    return generation;
}
