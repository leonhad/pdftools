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

void Font::SetSize(const double size)
{
    m_size = size;
}

double Font::Size() const
{
    return m_size;
}

bool Font::Fixed() const
{
    return m_fixed;
}

void Font::SetFixed(const bool fixed)
{
    m_fixed = fixed;
}

void Font::SetItalic(const bool italic)
{
    m_italic = italic;
}

bool Font::Italic() const
{
    return m_italic;
}

bool Font::Bold() const
{
    return m_bold;
}

void Font::SetName(const string& name)
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

void Font::SetCharMapStart(const string& value)
{
    m_char_map_start = value;
}

void Font::SetCharMapFinish(const string& value)
{
    m_char_map_finish = value;
}

void Font::AddCharMap(const string& character, const string& utf16value)
{
    m_charmap [character] = UTF16beToUTF8(utf16value);
}

string Font::Translate(string &value)
{
    string ret;
    const size_t size = m_char_map_start.size();

    if (m_charmap.empty())
    {
        return value;
    }

    const char *start = m_char_map_start.c_str();
    const char *finish = m_char_map_finish.c_str();

    const char *buffer = value.c_str();
    const size_t length = value.size();
    for (size_t loop = 0; loop < length; loop++, buffer += size)
    {
        const int f = memcmp(start, buffer, m_char_map_start.length());
        if (const int s = memcmp(finish, buffer, m_char_map_finish.length()); f <= 0 && s >= 0)
        {
            auto c = string(buffer, size);
            ret += m_charmap [c];
        }
        else
        {
            ret += *buffer;
        }
    }
    return ret;
}
