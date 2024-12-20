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
#include "pageanalyze.h"
#include "graphics/graphicstate.h"
#include "glyphs/glyphs.h"
#include "semantic/font.h"
#include "nodes/nodes.h"
#include "semantic/document.h"

using namespace node;

PageAnalyze::PageAnalyze(const std::shared_ptr<Document>& document) :
    m_document(document), m_root(nullptr)
{
}


std::shared_ptr<Glyph> PageAnalyze::AnalyzeTree(const std::shared_ptr<RootNode>& tree)
{
    m_root = std::make_shared<Glyph>();
    AnalyzeTree(tree, m_root);
    return m_root;
}

void PageAnalyze::AnalyzeTree(const std::shared_ptr<RootNode>& tree, const std::shared_ptr<Glyph>& parent)
{
    const auto& node_parent = parent;
    const size_t size = tree->Size();
    for (size_t loop = 0; loop < size; loop++)
    {
        const auto node = tree->Get(loop);

        if (m_document->TreeRoot())
        {
            if (const auto bdc = std::dynamic_pointer_cast<BDCNode>(node))
            {
                if (bdc->Name() == "/P")
                {
                    std::shared_ptr<Glyph> p(new ParagraphGlyph);
                    AnalyzeTree(bdc, p);
                    node_parent->AddChild(p);
                }
                else if (bdc->Name() == "/Artifact")
                {
                    const auto attr = std::dynamic_pointer_cast<MapNode>(bdc->Value());
                    if (const auto type = std::dynamic_pointer_cast<NameNode>(attr->Get("/Type")); !type || type->Name()
                        != "/Pagination")
                    {
                        AnalyzeTree(bdc, node_parent);
                    }
                }
                else
                {
                    AnalyzeTree(bdc, node_parent);
                }

                continue;
            }
        }
        else
        {
            if (const auto bdc = std::dynamic_pointer_cast<BDCNode>(node))
            {
                AnalyzeTree(bdc, node_parent);
            }
        }

        if (const auto text_matrix = std::dynamic_pointer_cast<TextMatrixNode>(node))
        {
            node_parent->AddChild(AnalyzeTextMatrix(text_matrix));
            continue;
        }

        if (const auto font = std::dynamic_pointer_cast<FontNode>(node))
        {
            node_parent->AddChild(AnalyzeFont(font));
            continue;
        }

        if (const auto text = std::dynamic_pointer_cast<TextNode>(node))
        {
            AnalyzeText(text, node_parent);
            continue;
        }

        if (const auto state_node = std::dynamic_pointer_cast<StateNode>(node))
        {
            if (state_node->Save())
            {
                this->m_state.Push();
            }
            else
            {
                this->m_state.Pop();
            }
        }
    }
}

std::shared_ptr<FontGlyph> PageAnalyze::AnalyzeFont(const std::shared_ptr<FontNode>& font)
{
    return std::make_shared<FontGlyph>(font->Name(), font->Size() * m_state.GetTextFont());
}

void PageAnalyze::AnalyzeText(const std::shared_ptr<TextNode>& text, const std::shared_ptr<Glyph>& parent)
{
    parent->AddChild(std::make_shared<TextGlyph>(text->Text()));
}

std::shared_ptr<FontSizeGlyph> PageAnalyze::AnalyzeTextMatrix(const std::shared_ptr<TextMatrixNode>& text_matrix)
{
    m_state.SetTextMatrix(text_matrix->At(0), text_matrix->At(1), text_matrix->At(2),
                          text_matrix->At(3), text_matrix->At(4), text_matrix->At(5));
    return std::make_shared<FontSizeGlyph>(m_state.GetTextFont());
}
