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
#ifndef CONTEXT_H
#define CONTEXT_H

#include <string>

class Document;
class Font;
class Page;

class Context
{
private:
    Document *m_document;
    Page *m_page;
    Font *m_font;
    bool m_font_changed;
    bool m_use_font;
    double m_font_size;

public:
    Context(Document *document);
    ~Context();

    void set_use_font(bool use_font);
    void set_font_changed(bool changed);
    void set_current_font(std::string &alias, int size);
    void set_current_page(Page *page);
    void set_font_size(double size);

    bool use_font();
    bool font_changed();
    Font *font();
    double font_size();
    Document *document();
};

#endif
