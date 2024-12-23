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
#pragma once

#include <string>
#include <map>

class Font
{
    bool m_italic;
    bool m_bold;
    bool m_fixed;
    double m_size;
    std::string m_name;
    std::string m_char_map_start;
    std::string m_char_map_finish;
    std::map<std::string, std::string> m_charmap;

public:
    Font();
    ~Font() = default;

    void SetSize(double size);
    void SetFixed(bool fixed);
    void SetName(const std::string& name);
    void SetItalic(bool italic);
    std::string Name();
    double Size() const;
    bool Italic() const;
    bool Bold() const;
    bool Fixed() const;

    void SetCharMapStart(const std::string& value);
    void SetCharMapFinish(const std::string& value);
    void AddCharMap(const std::string& character, const std::string& utf16value);
    std::string Translate(std::string &value);
};
