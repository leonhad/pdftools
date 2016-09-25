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
#include "page.h"
#include "context.h"
#include "document.h"
#include "glyphs/glyph.h"
#include "html/html.h"
#include <cstdlib>
#include <stdint.h>
#include <string.h>

using namespace std;

Page::Page(Document *parent)
{
    m_media_box = nullptr;
    m_crop_box = nullptr;
    m_document = parent;
    m_id = 0;
    m_generation = 0;
    m_root = nullptr;
}

Page::~Page()
{
    if (m_media_box)
    {
        delete [] m_media_box;
    }

    if (m_crop_box)
    {
        delete [] m_crop_box;
    }

    if (m_root)
    {
        delete m_root;
    }
}

void Page::set_root(Glyph *root)
{
    m_root = root;
}

void Page::add_fontmap(string alias, string font_name)
{
    m_fontmap[alias] = font_name;
}

string Page::font_name(string &alias)
{
    return m_fontmap[alias];
}

void Page::execute(Html *html)
{
    Context *context = new Context(m_document);
    context->set_current_page(this);
    html->addSection(link());
    m_root->execute(html, context);
    html->endTag();
    delete context;
}

const string Page::link()
{
    return m_link;
}

void Page::set_media_box(int a, int b, int c, int d)
{
    m_media_box = new int[4];
    m_media_box[0] = a;
    m_media_box[1] = b;
    m_media_box[2] = c;
    m_media_box[3] = d;
}

void Page::set_crop_box(int a, int b, int c, int d)
{
    m_crop_box = new int[4];
    m_crop_box[0] = a;
    m_crop_box[1] = b;
    m_crop_box[2] = c;
    m_crop_box[3] = d;
}

void Page::set_destination(int id, int generation)
{
    m_id = id;
    m_generation = generation;

    m_link = "section" + to_string(id) + "_" + to_string(generation);
}

int Page::id()
{
    return m_id;
}

int Page::generation()
{
    return m_generation;
}
