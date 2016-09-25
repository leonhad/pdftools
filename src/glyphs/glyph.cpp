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
#include "html/html.h"
#include "glyph.h"

using namespace std;

Glyph::Glyph() : m_context(nullptr), m_last_glyph(nullptr)
{
}

Glyph::~Glyph()
{
    vector<Glyph *>::iterator i;
    for (i = m_childs.begin(); i != m_childs.end(); i++)
    {
        delete *i;
    }
}

void Glyph::add_child(Glyph *glyph)
{
    if (glyph)
    {
        m_childs.push_back(glyph);
    }
}

void Glyph::execute(Html *document, Context *context)
{
    m_context = context;

    start_glyph(document);
    do_glyph(document);

    unsigned long size = m_childs.size();
    if (size > 0)
    {
        m_last_glyph = this;
    }

    for (size_t i = 0; i < size; i++)
    {
        m_childs[i]->set_last(m_last_glyph);
        m_childs[i]->execute(document, context);
        m_last_glyph = m_childs[i];
    }
    end_glyph(document);
}

void Glyph::set_last(Glyph *glyph)
{
    m_last_glyph = glyph;
}

void Glyph::do_glyph(Html *)
{
}

void Glyph::start_glyph(Html *)
{
}

void Glyph::end_glyph(Html *)
{
}
