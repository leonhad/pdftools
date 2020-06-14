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
#ifndef GLYPH_H
#define GLYPH_H

#include <vector>

class Html;

class Context;

/**
 * Draw a HTML glyph.
 */
class Glyph
{
private:
    /**
     * The childhood list.
     */
    std::vector<Glyph *> m_childs;

protected:
    /**
     * The context used in drawing.
     */
    Context *m_context;

    /**
     * The last glyph used.
     */
    Glyph *m_lastGlyph;

public:
    /**
     * Creates a new instance.
     */
    Glyph();

    /**
     * Destroy this instance.
     */
    virtual ~Glyph();

    /**
     * Add a child to this glyph.
     *
     * @param glyph the child to add.
     */
    void AddChild(Glyph *glyph);

    /**
     * Draw this list into HTML document.
     *
     * @param document the document to draw.
     * @param context the variable context used in this process.
     */
    void Execute(Html *document, Context *context);

    /**
     * Draw this glyph.
     *
     * @param document the document to generate in.
     */
    virtual void DoGlyph(Html *document);

    /**
     * Called before the drawing.
     *
     * @param document the document.
     */
    virtual void StartGlyph(Html *document);

    /**
     * Called after the drawing.
     *
     * @param document the document.
     */
    virtual void EndGlyph(Html *document);

    /**
     * Sets the last used glyph.
     *
     * @param glyph the last used glyph.
     */
    void SetLast(Glyph *glyph);
};

#endif
