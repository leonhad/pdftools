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
#include "pagelabel.h"

#include <iostream>

PageLabel::PageLabel(int start, int range, page_type type, string &name)
{
    m_start_number = start;
    m_range = range;
    m_type = type;
    m_name = name;
}

int PageLabel::start()
{
    return m_start_number;
}

int PageLabel::range()
{
    return m_range;
}

page_type PageLabel::type()
{
    return m_type;
}

string &PageLabel::name()
{
    return m_name;
}
