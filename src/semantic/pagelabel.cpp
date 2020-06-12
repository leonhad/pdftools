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
#include "pagelabel.h"

#include <iostream>

using namespace std;

PageLabel::PageLabel(int start, int range, page_type type, string &name)
{
    this->startNumber = start;
    this->range = range;
    this->type = type;
    this->name = name;
}

int PageLabel::Start()
{
    return startNumber;
}

int PageLabel::Range()
{
    return range;
}

page_type PageLabel::Type()
{
    return type;
}

string &PageLabel::Name()
{
    return name;
}
