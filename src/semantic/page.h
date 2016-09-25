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
#ifndef PAGE_H
#define PAGE_H

#include <string>
#include <map>

class Context;
class Document;
class Glyph;
class Html;

class Page
{
private:
    int *m_media_box;
    int *m_crop_box;
    int m_id;
    int m_generation;
    std::string m_link;
    Glyph *m_root;
    Document *m_document;
    std::map<std::string, std::string> m_fontmap;

public:
    Page(Document *parent);
    ~Page();

    void set_media_box(int a, int b, int c, int d);
    void set_crop_box(int a, int b, int c, int d);
    void set_destination(int id, int generation);
    void set_root(Glyph *root);
    int id();
    int generation();
    const std::string link();

    void execute(Html *html);

    void add_fontmap(std::string alias, std::string font_name);
    std::string font_name(std::string &alias);
};

#endif
