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
    mediaBox = nullptr;
    cropBox = nullptr;
    document = parent;
    id = 0;
    generation = 0;
    root = nullptr;
}

Page::~Page()
{
    if (mediaBox)
    {
        delete [] mediaBox;
    }

    if (cropBox)
    {
        delete [] cropBox;
    }

    if (root)
    {
        delete root;
    }
}

void Page::SetRoot(Glyph *r)
{
    this->root = r;
}

void Page::AddFontMap(string alias, string font_name)
{
    fontMap [alias] = font_name;
}

string Page::FontName(string &alias)
{
    return fontMap [alias];
}

void Page::Execute(Html *html)
{
    Context *context = new Context(document);
    context->setCurrentPage(this);
    html->AddSection(Link());
    root->Execute(html, context);
    html->EndTag();
    delete context;
}

const string Page::Link()
{
    return link;
}

void Page::SetMediaBox(int a, int b, int c, int d)
{
    mediaBox = new int [4];
    mediaBox [0] = a;
    mediaBox [1] = b;
    mediaBox [2] = c;
    mediaBox [3] = d;
}

void Page::SetCropBox(int a, int b, int c, int d)
{
    cropBox = new int [4];
    cropBox [0] = a;
    cropBox [1] = b;
    cropBox [2] = c;
    cropBox [3] = d;
}

void Page::SetDestination(int i, int g)
{
    this->id = i;
    this->generation = g;

    this->link = "section" + to_string(id) + "_" + to_string(generation);
}

int Page::Id()
{
    return id;
}

int Page::Generation()
{
    return generation;
}
