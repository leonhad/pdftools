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
#ifndef PAGEANALYZE_H
#define PAGEANALYZE_H

#include "graphics/graphicstate.h"
#include "glyphs/glyphs.h"

class Font;
class Document;

namespace node
{
    class TreeNode;
    class TextNode;
    class RootNode;
    class FontNode;
    class TextMatrixNode;
}

class PageAnalyze
{
private:
    GraphicState state;
    Document *document;
    Glyph *root;

public:
    PageAnalyze(Document *document);
    ~PageAnalyze();

    Glyph *AnalyzeTree(node::RootNode *tree);

private:
    void AnalyzeTree(node::RootNode *tree, Glyph *parent);
    void AnalyzeText(node::TextNode *text, Glyph *parent);
    FontSizeGlyph *AnalyzeTextMatrix(node::TextMatrixNode *text_matrix);
    FontGlyph *AnalyzeFont(node::FontNode *font);
};

#endif
