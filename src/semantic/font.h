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

    void set_size(double size);
    void set_fixed(bool fixed);
    void set_name(std::string name);
    void set_italic(bool italic);
    std::string name();
    double size();
    bool italic();
    bool bold();
    bool fixed();

    void set_charmap_start(std::string value);
    void set_charmap_finish(std::string value);
    void add_charmap(std::string character, std::string utf16value);
    std::string translate(std::string &value);
};

#endif
