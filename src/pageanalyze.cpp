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
#include <cstdlib>

using namespace node;

PageAnalyze::PageAnalyze(Document *document) :
        document(document), root(nullptr)
{
}

PageAnalyze::~PageAnalyze()
{
}

Glyph *PageAnalyze::AnalyzeTree(RootNode *tree)
{
    root = new Glyph;
    AnalyzeTree(tree, root);
    return root;
}

void PageAnalyze::AnalyzeTree(RootNode *tree, Glyph *parent)
{
    Glyph *node_parent = parent;
    size_t size = tree->Size();
    for (size_t loop = 0; loop < size; loop++)
    {
        TreeNode *node = tree->Get(loop);

        if (document->treeRoot())
        {
            BDCNode *bdc = dynamic_cast<BDCNode *>(node);
            if (bdc)
            {
                if (bdc->Name() == "/P")
                {
                    ParagraphGlyph *p = new ParagraphGlyph;
                    AnalyzeTree(bdc, p);
                    node_parent->AddChild(p);
                }
                else if (bdc->Name() == "/Artifact")
                {
                    MapNode *attr = dynamic_cast<MapNode *>(bdc->Value());
                    NameNode *type = dynamic_cast<NameNode *>(attr->Get("/Type"));
                    if (type && type->Name() == "/Pagination")
                    {
                        // Ignore
                        continue;
                    }
                    else
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
            BDCNode *bdc = dynamic_cast<BDCNode *>(node);
            if (bdc)
            {
                AnalyzeTree(bdc, node_parent);
            }
        }

        TextMatrixNode *text_matrix = dynamic_cast<TextMatrixNode *>(node);
        if (text_matrix)
        {
            node_parent->AddChild(AnalyzeTextMatrix(text_matrix));
            continue;
        }

        FontNode *font = dynamic_cast<FontNode *>(node);
        if (font)
        {
            node_parent->AddChild(AnalyzeFont(font));
            continue;
        }

        TextNode *text = dynamic_cast<TextNode *>(node);
        if (text)
        {
            AnalyzeText(text, node_parent);
            continue;
        }

        StateNode *stateNode = dynamic_cast<StateNode *>(node);
        if (stateNode)
        {
            if (stateNode->Save())
            {
                this->state.Push();
            }
            else
            {
                this->state.Pop();
            }
        }
    }
}

FontGlyph *PageAnalyze::AnalyzeFont(FontNode *font)
{
    return new FontGlyph(font->Name(), font->Size() * state.GetTextFont());
}

void PageAnalyze::AnalyzeText(TextNode *text, Glyph *parent)
{
    parent->AddChild(new TextGlyph(text->Text()));
}

FontSizeGlyph *PageAnalyze::AnalyzeTextMatrix(TextMatrixNode *text_matrix)
{
    state.SetTextMatrix(text_matrix->At(0), text_matrix->At(1), text_matrix->At(2),
            text_matrix->At(3), text_matrix->At(4), text_matrix->At(5));
    return new FontSizeGlyph(state.GetTextFont());
}
