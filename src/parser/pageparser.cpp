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
#include "utils.h"
#include "token.h"
#include "nodes/nodes.h"
#include "glyphs/glyphs.h"
#include <iostream>

using namespace std;
using namespace parser;
using namespace node;

PageParser::PageParser(istream *stream) : GenericParser{stream}
{
    m_scanner->disableCharsetConversion();
}

PageParser::~PageParser()
{
    if (m_root)
    {
        delete m_root;
    }
}

RootNode *PageParser::parse()
{
    if (m_root)
    {
        delete m_root;
    }
    m_root = new RootNode();
    RootNode *root = m_root;

    vector<TreeNode *> values;
    values.reserve(10);

    nextToken();
    while (m_scanner->good())
    {
        TreeNode *value = valueSequence();
        if (value)
        {
            values.push_back(value);
        }
        else
        {
            switch (m_token->type())
            {
            case TokenType::BDC:
                root = bdcSequence(values, root);
                break;
            case TokenType::EMC:
            {
                match(TokenType::EMC);
                BDCNode *bdc = dynamic_cast<BDCNode *> (root);
                if (bdc)
                {
                    root = bdc->parent();
                }
                break;
            }
            case TokenType::BI:
                root->addChild(biSequence());
                break;

                // Text positioning
            case TokenType::TM:
                root->addChild(tmSequence(values));
                break;

            case TokenType::TF:
                root->addChild(fontSequence(values));
                break;

                // Graphic State
            case TokenType::Q_LO:
                root->addChild(new StateNode(true));
                    nextToken();
                break;
            case TokenType::Q_UP:
                root->addChild(new StateNode(false));
                    nextToken();
                break;

                // Text
            case TokenType::TJ_LO:
                match(TokenType::TJ_LO);
                    root->addChild(textSequence(values));
                break;
            case TokenType::TJ_UP:
                tjupSequence(root, values);
                break;
            case TokenType::T_AST:
                match(TokenType::T_AST);
                    root->addChild(new BreakNode);
                break;
            case TokenType::DOUBLE_QUOTE:
            {
                match(TokenType::DOUBLE_QUOTE);
                root->addChild(new BreakNode);
                vector<TreeNode *> vector;
                vector.assign(values.begin() + 3, values.end());
                root->addChild(textSequence(vector));
                break;
            }
            case TokenType::QUOTE:
                match(TokenType::QUOTE);
                    root->addChild(new BreakNode);
                    root->addChild(textSequence(values));
                    nextToken();
                break;
            default:
                nextToken();
                break;
            }
            size_t size = values.size();
            for (size_t loop = 0; loop < size; loop++)
            {
                if (values[loop])
                {
                    delete values[loop];
                }
            }
            values.clear();
        }
    }
    return m_root;
}

TreeNode *PageParser::tmSequence(vector<TreeNode *> &values)
{
    match(TokenType::TM);

    if (values.size() == 6)
    {
        NumberNode *a = dynamic_cast<NumberNode *> (values[0]);
        NumberNode *b = dynamic_cast<NumberNode *> (values[1]);
        NumberNode *c = dynamic_cast<NumberNode *> (values[2]);
        NumberNode *d = dynamic_cast<NumberNode *> (values[3]);
        NumberNode *e = dynamic_cast<NumberNode *> (values[4]);
        NumberNode *f = dynamic_cast<NumberNode *> (values[5]);

        return new TextMatrixNode({a->value(), b->value(), c->value(), d->value(), e->value(), f->value()});
    }
    return nullptr;
}

TreeNode *PageParser::fontSequence(vector<TreeNode *> &values)
{
    match(TokenType::TF);

    if (values.size() == 2)
    {
        FontNode *font = new FontNode;

        NameNode *font_name = dynamic_cast<NameNode *> (values[0]);
        if (font_name)
        {
            font->setName(font_name->name());
        }
        NumberNode *font_size = dynamic_cast<NumberNode *> (values[1]);
        if (font_size)
        {
            font->setSize(font_size->value());
        }
        return font;
    }
    else
    {
        error_message("Error parsing font object");
        return nullptr;
    }
}

TreeNode *PageParser::biSequence()
{
    match(TokenType::BI);
    while (m_token->type() != TokenType::ID)
    {
        match(TokenType::NAME);
        TreeNode *value = valueSequence();
        delete value;
    }
    m_scanner->getImageStream();
    nextToken();
    match(TokenType::EI);
    return nullptr;
}

TreeNode *PageParser::textSequence(vector<TreeNode *> &values)
{
    TextNode *text = new TextNode;
    size_t size = values.size();
    for (size_t loop = 0; loop < size; loop++)
    {
        StringNode *node = dynamic_cast<StringNode *> (values[loop]);
        if (node)
        {
            text->add(node->value());
        }
    }
    return text;
}

void PageParser::tjupSequence(RootNode *root, vector<TreeNode *> &values)
{
    match(TokenType::TJ_UP);
    size_t size = values.size();
    for (size_t loop = 0; loop < size; loop++)
    {
        ArrayNode *array = dynamic_cast<ArrayNode *> (values[loop]);
        if (array)
        {
            size_t array_size = array->size();
            for (size_t y = 0; y < array_size; y++)
            {
                StringNode *node = dynamic_cast<StringNode *> (array->value(y));
                if (node)
                {
                    TextNode *text = new TextNode;
                    text->add(node->value());
                    root->addChild(text);
                }
            }
        }
    }
}

BDCNode *PageParser::bdcSequence(vector<TreeNode *> &values, RootNode *parent)
{
    match(TokenType::BDC);
    BDCNode *node = new BDCNode(parent);
    parent->addChild(node);

    NameNode *name = dynamic_cast<NameNode *> (values[0]);
    if (name)
    {
        node->setName(name->name());
    }
    node->setValue(values[1]);
    // avoid double delete
    values[1] = nullptr;

    return node;
}
