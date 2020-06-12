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
#ifndef OUTLINE_H
#define OUTLINE_H

#include <vector>
#include <string>

class Outline
{
private:
    std::vector<Outline *> childs;
    std::string title;
    int id;
    int generation;
    double x;
    double y;

public:
    Outline();
    ~Outline();

    void AddChild(Outline *child);
    void SetDestination(int id, int generation);
    void SetLocation(double x, double y);
    void SetTitle(std::string title);

    int Id();
    int Generation();
    const char *Title();

    size_t Size();
    Outline *Child(size_t index);
};

#endif
