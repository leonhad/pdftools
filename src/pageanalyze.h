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
#ifndef PAGEANALYZE_H
#define PAGEANALYZE_H

#include "graphics/graphicstate.h"
#include "glyphs/glyphs.h"

class Font;
class Document;

namespace node {
    class TreeNode;
    class TextNode;
    class RootNode;
    class FontNode;
    class TextMatrixNode;
}

class PageAnalyze {
private:
    GraphicState m_state;
    Document *m_document;
    Glyph *m_root;
    Font *m_font;

public:
    PageAnalyze(Document *document);
    ~PageAnalyze();

    Glyph *analyze_tree(node::RootNode *tree);

private:
    void analyze_tree(node::RootNode *tree, Glyph *parent);
    void analyze_text(node::TextNode *text, Glyph *parent);
    FontSizeGlyph *analyze_text_matrix(node::TextMatrixNode *text_matrix);
    FontGlyph *analyze_font(node::FontNode *font);
};

#endif
