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

void Glyph::AddChild(const std::shared_ptr<Glyph>& glyph)
{
    if (glyph)
    {
        m_children.push_back(glyph);
    }
}

void Glyph::Execute(const std::shared_ptr<Html>& document, const std::shared_ptr<Context>& context)
{
    this->m_context = context;

    StartGlyph(document);
    DoGlyph(document);

    const size_t size = m_children.size();
    if (size > 0)
    {
        m_lastGlyph = std::shared_ptr<Glyph>(this);
    }

    for (size_t i = 0; i < size; i++)
    {
        m_children[i]->SetLast(m_lastGlyph);
        m_children[i]->Execute(document, m_context);
        m_lastGlyph = m_children[i];
    }

    EndGlyph(document);
}

void Glyph::SetLast(const std::shared_ptr<Glyph>& glyph)
{
    this->m_lastGlyph = glyph;
}

void Glyph::DoGlyph(const std::shared_ptr<Html>&)
{
}

void Glyph::StartGlyph(const std::shared_ptr<Html>&)
{
}

void Glyph::EndGlyph(const std::shared_ptr<Html>&)
{
}
