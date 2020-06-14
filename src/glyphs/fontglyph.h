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
#ifndef FONTGLYPH_H
#define FONTGLYPH_H

#include <string>
#include "glyph.h"

/**
 * Stores a font glyph.
 */
class FontGlyph: public Glyph
{
private:
    /**
     * The font size.
     */
    double m_size;

    /**
     * Font face name.
     */
    std::string m_font;

public:
    /**
     * Creates a new instance.
     *
     * @param font the font face name.
     * @param size the font size.
     */
    FontGlyph(std::string &&font, double size);

    /**
     * Draw this glyph.
     *
     * @param document the document to generate in.
     */
    virtual void DoGlyph(Html *document);
};

#endif
