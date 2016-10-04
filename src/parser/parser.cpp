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
#include "parser.h"
#include "utils.h"
#include "nodes/nodes.h"

using namespace std;
using namespace parser;
using namespace node;

inline bool pdf_versions(const string &version)
{
    return version == "PDF-1.1"
            || version == "PDF-1.2"
            || version == "PDF-1.3"
            || version == "PDF-1.4"
            || version == "PDF-1.5"
            || version == "PDF-1.6"
            || version == "PDF-1.7";
}

Parser::Parser(ifstream *filein) throw(exception) : GenericParser{filein}
{
    m_linear = false;

    if (filein->is_open())
    {
        nextToken();
    }
    else
    {
        throw ios_base::failure("Invalid input file.");
    }
}

RootNode *Parser::parse()
{
    RootNode *root = new RootNode();
    bool error = false;
    match(TokenType::PERCENT);
    if (verify_version())
    {
        while (m_scanner->good() && !error)
        {
            switch (m_token->type())
            {
                case TokenType::PERCENT:
                    comment_sequence();
                    break;
                case TokenType::NUM:
                    root->addChild(object_sequence());
                    break;
                case TokenType::XREF:
                    root->addChild(xref_sequence());
                    break;
                case TokenType::START_XREF:
                    startxref_sequence();
                    break;
                default:
                    nextToken();
                    error = true;
                    break;
            }
        }
    }
    else
    {
        error_message("invalid input file");
    }
    m_scanner->clear();
    object_streams(root);
    return root;
}

void Parser::object_streams(RootNode *root_node)
{
    size_t size = root_node->size();

    for (size_t i = 0; i < size; i++)
    {
        ObjNode *root_object = dynamic_cast<ObjNode *> (root_node->get(i));
        if (root_object)
        {
            MapNode *map = dynamic_cast<MapNode *> (root_object->value());
            if (map)
            {
                NameNode *type = dynamic_cast<NameNode *> (map->get("/Type"));
                if (type && type->name() == "/ObjStm")
                {
                    int qtd = 0;
                    int length = 0;
                    NumberNode *number = dynamic_cast<NumberNode *> (map->get("/N"));
                    if (number)
                    {
                        qtd = number->value();
                    }
                    NumberNode *length_node = dynamic_cast<NumberNode *> (map->get("/Length"));
                    if (number)
                    {
                        length = length_node->value();
                    }
                    char *uncompressed = nullptr;

                    m_scanner->to_pos(root_object->streamPos());
                    char *stream = m_scanner->get_stream(length);

                    int total = length;
                    NameNode *filter = dynamic_cast<NameNode *> (map->get("/Filter"));
                    if (filter && filter->name() == "/FlateDecode")
                    {
                        uncompressed = flat_decode(stream, length, total);
                        delete[] stream;
                    }
                    else if (!filter)
                    {
                        uncompressed = stream;
                    }
                    else
                    {
                        string msg{"compression not supported: "};
                        msg += filter->name();
                        error_message(msg.c_str());
                        return;
                    }
                    stringstream stream_value;
                    stream_value.write(uncompressed, total);
                    stream_value.seekg(0);
                    delete[] uncompressed;

                    Scanner *temp = m_scanner;
                    m_scanner = new Scanner{&stream_value};

                    vector<int> ids;
                    int loop;
                    for (loop = 0; loop < qtd; loop++)
                    {
                        nextToken();
                        ids.push_back(m_token->toNumber());
                        nextToken();
                    }
                    nextToken();
                    vector<int>::iterator id;
                    for (id = ids.begin(); id < ids.end(); id++)
                    {
                        ObjNode *new_obj = new ObjNode(*id, 0);
                        new_obj->setValue(valueSequence());
                        root_node->addChild(new_obj);
                    }
                    m_scanner = temp;
                }
            }
        }
    }
}

void Parser::comment_sequence()
{
    m_scanner->ignore_line();
    nextToken();
}

TreeNode *Parser::xref_sequence()
{
    XREFNode *xref = new XREFNode;
    match(TokenType::XREF);

    do
    {
        uint16_t id = (uint16_t) m_token->toNumber();
        match(TokenType::NUM);
        int count = (int) m_token->toNumber();
        match(TokenType::NUM);

        for (int loop = 0; loop < count; loop++)
        {
            uint32_t address = (uint32_t) m_token->toNumber();
            match(TokenType::NUM);
            uint16_t generation = (uint16_t) m_token->toNumber();
            match(TokenType::NUM);
            string name = m_token->value();
            if (m_token->type() == TokenType::F_LO)
            {
                match(TokenType::F_LO);
            }
            else
            {
                match(TokenType::N);
            }
            xref->addNode(id, generation, address, name.at(0));
            id++;
        }
    } while (m_scanner->good() && (m_token->type() != TokenType::TRAILER));
    match(TokenType::TRAILER);
    xref->setTrailer(valueSequence());
    return xref;
}

void Parser::startxref_sequence()
{
    match(TokenType::START_XREF);
    match(TokenType::NUM);

    match(TokenType::PERCENT);
    match(TokenType::PERCENT);
    match(TokenType::END_PDF);
}

TreeNode *Parser::object_sequence()
{
    float number = m_token->toNumber();
    match(TokenType::NUM);
    float generation_nunber = m_token->toNumber();
    match(TokenType::NUM);

    ObjNode *node = new ObjNode((int) number, (int) generation_nunber);
    match(TokenType::OBJ);
    node->setValue(valueSequence());
    if (m_token && m_token->type() == TokenType::STREAM)
    {
        int length = -1;
        MapNode *map = dynamic_cast<MapNode *> (node->value());
        if (map)
        {
            NumberNode *numberNode = dynamic_cast<NumberNode *> (map->get("/Length"));
            if (numberNode)
            {
                length = numberNode->value();
            }
        }
        node->setStreamPos(m_scanner->ignore_stream(length));
        nextToken();
        match(TokenType::END_STREAM);
    }
    match(TokenType::END_OBJ);

    return node;
}

bool Parser::verify_version()
{
    if (m_token)
    {
        string line = m_token->value();
        if (pdf_versions(line))
        {
            match(TokenType::NAME);
            return true;
        }
    }
    return false;
}
