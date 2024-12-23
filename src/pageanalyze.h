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
#pragma once

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
    GraphicState m_state;
    std::shared_ptr<Document> m_document;
    std::shared_ptr<Glyph> m_root;

public:
    explicit PageAnalyze(const std::shared_ptr<Document>& document);
    ~PageAnalyze() = default;

    std::shared_ptr<Glyph> AnalyzeTree(const std::shared_ptr<node::RootNode>& tree);

private:
    void AnalyzeTree(const std::shared_ptr<node::RootNode>& tree, const std::shared_ptr<Glyph>& parent);
    static void AnalyzeText(const std::shared_ptr<node::TextNode>& text, const std::shared_ptr<Glyph>& parent);
    std::shared_ptr<FontSizeGlyph> AnalyzeTextMatrix(const std::shared_ptr<node::TextMatrixNode>& text_matrix) const;
    std::shared_ptr<FontGlyph> AnalyzeFont(const std::shared_ptr<node::FontNode>& font) const;
};
