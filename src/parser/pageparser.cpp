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
#include "pageparser.h"
#include "../utils.h"
#include "token.h"
#include "../nodes/nodes.h"
#include <iostream>

using namespace std;
using namespace parser;
using namespace node;

PageParser::PageParser(istream *stream) : GenericParser{stream}
{
    m_scanner->DisableCharsetConversion();
}

std::shared_ptr<RootNode> PageParser::Parse()
{
    m_root = make_shared<RootNode>();
    std::shared_ptr root{m_root};

    vector<std::shared_ptr<TreeNode>> values;
    values.reserve(10);

    NextToken();
    while (m_scanner->Good())
    {
        if (const auto value = ValueSequence())
        {
            values.push_back(value);
        }
        else
        {
            switch (m_token->Type())
            {
            case TokenType::BDC:
                root = BdcSequence(values, root);
                break;
            case TokenType::EMC:
                {
                    Match(TokenType::EMC);
                    if (auto bdc = std::dynamic_pointer_cast<BDCNode>(root))
                    {
                        root = bdc->Parent();
                    }
                    break;
                }
            case TokenType::BI:
                root->AddChild(BiSequence());
                break;

            // Text positioning
            case TokenType::TM:
                root->AddChild(TmSequence(values));
                break;

            case TokenType::TF:
                root->AddChild(FontSequence(values));
                break;

            // Graphic State
            case TokenType::Q_LO:
                root->AddChild(make_shared<StateNode>(true));
                NextToken();
                break;
            case TokenType::Q_UP:
                root->AddChild(make_shared<StateNode>(false));
                NextToken();
                break;

            // Text
            case TokenType::TJ_LO:
                Match(TokenType::TJ_LO);
                root->AddChild(TextSequence(values));
                break;
            case TokenType::TJ_UP:
                TjupSequence(root, values);
                break;
            case TokenType::T_AST:
                Match(TokenType::T_AST);
                root->AddChild(make_shared<BreakNode>());
                break;
            case TokenType::DOUBLE_QUOTE:
                {
                    Match(TokenType::DOUBLE_QUOTE);
                    root->AddChild( make_shared<BreakNode>());
                    vector<std::shared_ptr<TreeNode>> vector;
                    vector.assign(values.begin() + 3, values.end());
                    root->AddChild(TextSequence(vector));
                    break;
                }
            case TokenType::QUOTE:
                Match(TokenType::QUOTE);
                root->AddChild(make_shared<BreakNode>());
                root->AddChild(TextSequence(values));
                NextToken();
                break;
            default:
                NextToken();
                break;
            }

            values.clear();
        }
    }

    return m_root;
}

std::shared_ptr<TreeNode> PageParser::TmSequence(const vector<std::shared_ptr<TreeNode>>& values)
{
    Match(TokenType::TM);

    if (values.size() == 6)
    {
        const auto a = std::dynamic_pointer_cast<NumberNode>(values[0]);
        const auto b = std::dynamic_pointer_cast<NumberNode>(values[1]);
        const auto c = std::dynamic_pointer_cast<NumberNode>(values[2]);
        const auto d = std::dynamic_pointer_cast<NumberNode>(values[3]);
        const auto e = std::dynamic_pointer_cast<NumberNode>(values[4]);
        const auto f = std::dynamic_pointer_cast<NumberNode>(values[5]);

        return make_shared<TextMatrixNode>(initializer_list<double>{
            a->Value(), b->Value(), c->Value(), d->Value(), e->Value(), f->Value()
        });
    }
    return nullptr;
}

std::shared_ptr<TreeNode> PageParser::FontSequence(const vector<std::shared_ptr<TreeNode>>& values)
{
    Match(TokenType::TF);

    if (values.size() == 2)
    {
        std::shared_ptr<FontNode> font(new FontNode);

        if (const auto font_name = std::dynamic_pointer_cast<NameNode>(values[0]))
        {
            font->SetName(font_name->Name());
        }

        if (const auto font_size = std::dynamic_pointer_cast<NumberNode>(values[1]))
        {
            font->SetSize(font_size->Value());
        }

        return font;
    }

    ErrorMessage(L"Error parsing font object");
    return nullptr;
}

std::shared_ptr<TreeNode> PageParser::BiSequence()
{
    Match(TokenType::BI);
    while (m_token->Type() != TokenType::ID)
    {
        Match(TokenType::NAME);
        auto value = ValueSequence();
        // discard the result.
    }

    m_scanner->ImageStream();
    NextToken();
    Match(TokenType::EI);
    return nullptr;
}

std::shared_ptr<TreeNode> PageParser::TextSequence(const vector<std::shared_ptr<TreeNode>>& values)
{
    std::shared_ptr<TextNode> text(new TextNode);
    const size_t size = values.size();
    for (size_t loop = 0; loop < size; loop++)
    {
        if (const auto node = std::dynamic_pointer_cast<StringNode>(values[loop]))
        {
            text->Add(node->Value());
        }
    }

    return text;
}

void PageParser::TjupSequence(const std::shared_ptr<RootNode>& root, const vector<std::shared_ptr<TreeNode>>& values)
{
    Match(TokenType::TJ_UP);
    const size_t size = values.size();
    for (size_t loop = 0; loop < size; loop++)
    {
        if (const auto array = std::dynamic_pointer_cast<ArrayNode>(values[loop]))
        {
            const size_t array_size = array->Size();
            for (size_t y = 0; y < array_size; y++)
            {
                if (const auto node = std::dynamic_pointer_cast<StringNode>(array->Value(y)))
                {
                    std::shared_ptr<TextNode> text(new TextNode);
                    text->Add(node->Value());
                    root->AddChild(text);
                }
            }
        }
    }
}

std::shared_ptr<BDCNode> PageParser::BdcSequence(vector<std::shared_ptr<TreeNode>>& values,
                                                 const std::shared_ptr<RootNode>& parent)
{
    Match(TokenType::BDC);

    auto node = make_shared<BDCNode>(parent);
    parent->AddChild(node);

    if (const auto name = std::dynamic_pointer_cast<NameNode>(values[0]))
    {
        node->SetName(name->Name());
    }

    node->SetValue(values[1]);

    // avoid double delete
    values[1] = nullptr;

    return node;
}
