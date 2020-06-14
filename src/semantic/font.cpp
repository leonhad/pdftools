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
#include "font.h"
#include "../utils.h"
#include <cstring>

using namespace std;

Font::Font()
{
    m_italic = false;
    m_bold = false;
    m_fixed = false;
    m_size = 0;
}

Font::~Font()
{
}

void Font::SetSize(double size)
{
    m_size = size;
}

double Font::Size()
{
    return m_size;
}

bool Font::Fixed()
{
    return m_fixed;
}

void Font::SetFixed(bool fixed)
{
    m_fixed = fixed;
}

void Font::SetItalic(bool italic)
{
    m_italic = italic;
}

bool Font::Italic()
{
    return m_italic;
}

bool Font::Bold()
{
    return m_bold;
}

void Font::SetName(string name)
{
    if (name.find("Bold") != string::npos)
    {
        m_bold = true;
    }
    m_name = name;
}

string Font::Name()
{
    return m_name;
}

void Font::SetCharMapStart(string value)
{
    m_charmap_start = value;
}

void Font::SetCharMapFinish(string value)
{
    m_charmap_finish = value;
}

void Font::AddCharMap(string character, string utf16value)
{
    m_charmap [character] = UTF16beToUTF8(utf16value);
}

string Font::Translate(string &value)
{
    string ret;
    size_t size = m_charmap_start.size();

    if (m_charmap.size() == 0)
    {
        return value;
    }

    const char *start = m_charmap_start.c_str();
    const char *finish = m_charmap_finish.c_str();

    const char *buffer = value.c_str();
    size_t length = value.size();
    for (size_t loop = 0; loop < length; loop++, buffer += size)
    {
        int f = memcmp(start, buffer, m_charmap_start.length());
        int s = memcmp(finish, buffer, m_charmap_finish.length());
        if (f <= 0 && s >= 0)
        {
            string c = string(buffer, size);
            ret += m_charmap [c];
        }
        else
        {
            ret += *buffer;
        }
    }
    return ret;
}
