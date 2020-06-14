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
#ifndef FONT_H
#define FONT_H

#include <string>
#include <map>

class Font
{
private:
    bool m_italic;
    bool m_bold;
    bool m_fixed;
    double m_size;
    std::string m_name;
    std::string m_charmap_start;
    std::string m_charmap_finish;
    std::map<std::string, std::string> m_charmap;

public:
    Font();
    ~Font();

    void SetSize(double size);
    void SetFixed(bool fixed);
    void SetName(std::string name);
    void SetItalic(bool italic);
    std::string Name();
    double Size();
    bool Italic();
    bool Bold();
    bool Fixed();

    void SetCharMapStart(std::string value);
    void SetCharMapFinish(std::string value);
    void AddCharMap(std::string character, std::string utf16value);
    std::string Translate(std::string &value);
};

#endif
