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
#include "pageanalyze.h"
#include "graphics/graphicstate.h"
#include "glyphs/glyphs.h"
#include "semantic/font.h"
#include "nodes/nodes.h"
#include "semantic/document.h"
#include <cstdlib>

using namespace node;

PageAnalyze::PageAnalyze(Document *document)
    : m_document(document), m_root(nullptr)
{
}

PageAnalyze::~PageAnalyze()
{
}

Glyph *PageAnalyze::analyze_tree(RootNode *tree)
{
    m_root = new Glyph;
    analyze_tree(tree, m_root);
    return m_root;
}

void PageAnalyze::analyze_tree(RootNode *tree, Glyph *parent)
{
    Glyph *node_parent = parent;
    size_t size = tree->size();
    for (size_t loop = 0; loop < size; loop++)
    {
        TreeNode *node = tree->get(loop);

        if (m_document->tree_root())
        {
            BDCNode *bdc = dynamic_cast<BDCNode *> (node);
            if (bdc)
            {
                if (bdc->name() == "/P")
                {
                    ParagraphGlyph *p = new ParagraphGlyph;
                    analyze_tree(bdc, p);
                    node_parent->add_child(p);
                }
                else if (bdc->name() == "/Artifact")
                {
                    MapNode *attr = dynamic_cast<MapNode *> (bdc->value());
                    NameNode *type = dynamic_cast<NameNode *> (attr->get("/Type"));
                    if (type && type->name() == "/Pagination")
                    {
                        // Ignore
                        continue;
                    }
                    else
                    {
                        analyze_tree(bdc, node_parent);
                    }
                }
                else
                {
                    analyze_tree(bdc, node_parent);
                }

                continue;
            }
        }
        else
        {
            BDCNode *bdc = dynamic_cast<BDCNode *> (node);
            if (bdc)
            {
                analyze_tree(bdc, node_parent);
            }
        }

        TextMatrixNode *text_matrix = dynamic_cast<TextMatrixNode *> (node);
        if (text_matrix)
        {
            node_parent->add_child(analyze_text_matrix(text_matrix));
            continue;
        }

        FontNode *font = dynamic_cast<FontNode *> (node);
        if (font)
        {
            node_parent->add_child(analyze_font(font));
            continue;
        }

        TextNode *text = dynamic_cast<TextNode *> (node);
        if (text)
        {
            analyze_text(text, node_parent);
            continue;
        }

        StateNode *state = dynamic_cast<StateNode *> (node);
        if (state)
        {
            if (state->save())
            {
                m_state.push();
            }
            else
            {
                m_state.pop();
            }
        }
    }
}

FontGlyph *PageAnalyze::analyze_font(FontNode *font)
{
    return new FontGlyph(font->name(), font->size() * m_state.get_text_font());
}

void PageAnalyze::analyze_text(TextNode *text, Glyph *parent)
{
    parent->add_child(new TextGlyph(text->text()));
}

FontSizeGlyph *PageAnalyze::analyze_text_matrix(TextMatrixNode *text_matrix)
{
    m_state.set_text_matrix(text_matrix->at(0), text_matrix->at(1), text_matrix->at(2),
                            text_matrix->at(3), text_matrix->at(4), text_matrix->at(5));
    return new FontSizeGlyph(m_state.get_text_font());
}
