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
#include "page.h"
#include "context.h"
#include "document.h"
#include "../glyphs/glyph.h"
#include "../html/html.h"

using namespace std;

Page::Page(Document *parent)
{
    m_mediaBox = nullptr;
    m_cropBox = nullptr;
    m_document = parent;
    m_id = 0;
    m_generation = 0;
    m_root = nullptr;
}

Page::~Page()
{
    if (m_mediaBox)
    {
        delete [] m_mediaBox;
    }

    if (m_cropBox)
    {
        delete [] m_cropBox;
    }

    if (m_root)
    {
        delete m_root;
    }
}

void Page::SetRoot(Glyph *r)
{
    this->m_root = r;
}

void Page::AddFontMap(string alias, string font_name)
{
    m_fontMap [alias] = font_name;
}

string Page::FontName(string &alias)
{
    return m_fontMap [alias];
}

void Page::Execute(Html *html)
{
    Context *context = new Context(m_document);
    context->SetCurrentPage(this);
    html->AddSection(Link());
    m_root->Execute(html, context);
    html->EndTag();
    delete context;
}

const string Page::Link()
{
    return m_link;
}

void Page::SetMediaBox(int a, int b, int c, int d)
{
    m_mediaBox = new int [4];
    m_mediaBox [0] = a;
    m_mediaBox [1] = b;
    m_mediaBox [2] = c;
    m_mediaBox [3] = d;
}

void Page::SetCropBox(int a, int b, int c, int d)
{
    m_cropBox = new int [4];
    m_cropBox [0] = a;
    m_cropBox [1] = b;
    m_cropBox [2] = c;
    m_cropBox [3] = d;
}

void Page::SetDestination(int i, int g)
{
    this->m_id = i;
    this->m_generation = g;

    this->m_link = "section" + to_string(m_id) + "_" + to_string(m_generation);
}

int Page::Id()
{
    return m_id;
}

int Page::Generation()
{
    return m_generation;
}
