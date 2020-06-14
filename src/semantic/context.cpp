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
#include "context.h"
#include "document.h"
#include "page.h"
#include "font.h"
#include <cstdlib>

using namespace std;

Context::Context(class Document *document)
{
    m_document = document;
    m_page = nullptr;
    m_font = nullptr;
    m_font_changed = false;
    m_use_font = false;
    m_font_size = 1;
}

Context::~Context()
{
}

void Context::SetFontSize(double size)
{
    m_font_size = size;
}

double Context::FontSize()
{
    return m_font_size;
}

void Context::SetFontChanged(bool changed)
{
    m_font_changed = changed;
}

bool Context::FontChanged()
{
    return m_font_changed;
}

bool Context::UseFont()
{
    return m_use_font;
}

void Context::SetUseFont(bool use_font)
{
    m_use_font = use_font;
}

void Context::SetCurrentPage(Page *page)
{
    m_page = page;
}

Document *Context::Document()
{
    return m_document;
}

void Context::SetCurrentFont(string &alias, double size)
{
    if (m_document && m_page)
    {
        m_font_changed = true;
        m_font = m_document->Font(m_page->FontName(alias).c_str());
        m_font->SetSize(size);
    }
}

Font *Context::Font()
{
    return m_font;
}
