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
#ifndef OUTLINE_H
#define OUTLINE_H

#include <vector>
#include <string>

using namespace std;

class Outline {
private:
    vector<Outline *> m_childs;
    string m_title;
    int m_id;
    int m_generation;
    double m_x;
    double m_y;
    
public:
    Outline();
    ~Outline();
    
    void add_child(Outline *child);
    void set_destination(int id, int generation);
    void set_location(double x, double y);
    void set_title(string title);
    
    int id();
    int generation();
    const char *title();
    
    size_t size();
    Outline *child(size_t index);
};

#endif
