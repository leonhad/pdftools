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
#include "../html/html.h"
#include "glyph.h"

using namespace std;

Glyph::Glyph() : m_context(nullptr), m_lastGlyph(nullptr)
{
}

Glyph::~Glyph()
{
    vector<Glyph *>::iterator i;
    for (i = m_childs.begin(); i != m_childs.end(); ++i)
    {
        delete *i;
    }
}

void Glyph::AddChild(Glyph *glyph)
{
    if (glyph)
    {
        m_childs.push_back(glyph);
    }
}

void Glyph::Execute(Html *document, Context *c)
{
    this->m_context = c;

    StartGlyph(document);
    DoGlyph(document);

    size_t size = m_childs.size();
    if (size > 0)
    {
        m_lastGlyph = this;
    }

    for (size_t i = 0; i < size; i++)
    {
        m_childs [i]->SetLast(m_lastGlyph);
        m_childs [i]->Execute(document, m_context);
        m_lastGlyph = m_childs [i];
    }
    
    EndGlyph(document);
}

void Glyph::SetLast(Glyph *glyph)
{
    this->m_lastGlyph = glyph;
}

void Glyph::DoGlyph(Html *)
{
}

void Glyph::StartGlyph(Html *)
{
}

void Glyph::EndGlyph(Html *)
{
}
