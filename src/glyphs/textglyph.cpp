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
#include "textglyph.h"
#include "../html/html.h"
#include "../semantic/context.h"
#include "../semantic/font.h"

using namespace std;

TextGlyph::TextGlyph(string &&text) :
        m_text(move(text))
{
}

void TextGlyph::doGlyph(Html *document)
{
    Font *current = m_context->font();

    document->addFont(current->size() * m_context->fontSize(), current->bold(), current->italic(),
            current->fixed());
    string text = current->translate(m_text);

    document->addElement(text + " ");
    document->endTag();
}
