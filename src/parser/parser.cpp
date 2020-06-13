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
#include "../utils.h"
#include "../nodes/nodes.h"
#include "../genericexception.h"

using namespace std;
using namespace parser;
using namespace node;

inline bool pdf_versions(string const &version)
{
    return version == "PDF-1.1" || version == "PDF-1.2" || version == "PDF-1.3"
            || version == "PDF-1.4" || version == "PDF-1.5" || version == "PDF-1.6"
            || version == "PDF-1.7";
}

Parser::Parser(ifstream *filein) : GenericParser{ filein }
{
    m_linear = false;

    if (filein->is_open())
    {
        nextToken();
    }
    else
    {
        throw GenericException("Invalid input file.");
    }
}

RootNode *Parser::parse()
{
    RootNode *root = new RootNode();
    bool error = false;
    match(TokenType::PERCENT);
    if (verifyVersion())
    {
        while (m_scanner->good() && not error)
        {
            switch (m_token->type())
            {
            case TokenType::PERCENT:
                commentSequence();
                break;
            case TokenType::NUM:
                root->AddChild(objectSequence());
                break;
            case TokenType::XREF:
                root->AddChild(xrefSequence());
                break;
            case TokenType::START_XREF:
                startXrefSequence();
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
         throw GenericException("Invalid input file.");
    }
    m_scanner->clear();
    objectStreams(root);
    return root;
}

void Parser::objectStreams(RootNode *root_node)
{
    size_t size = root_node->Size();

    for (size_t i = 0; i < size; i++)
    {
        ObjNode *root_object = dynamic_cast<ObjNode *>(root_node->Get(i));
        if (root_object)
        {
            MapNode *map = dynamic_cast<MapNode *>(root_object->Value());
            if (map)
            {
                NameNode *type = dynamic_cast<NameNode *>(map->Get("/Type"));
                if (type && type->Name() == "/ObjStm")
                {
                    int qtd = 0;
                    size_t length = 0;
                    NumberNode *number = dynamic_cast<NumberNode *>(map->Get("/N"));
                    if (number)
                    {
                        qtd = (int) number->Value();
                    }
                    NumberNode *length_node = dynamic_cast<NumberNode *>(map->Get("/Length"));
                    if (number)
                    {
                        length = (size_t) length_node->Value();
                    }
                    char *uncompressed = nullptr;

                    m_scanner->to_pos(root_object->StreamPos());
                    char *stream = m_scanner->getStream((streamsize)length);

                    size_t total = (size_t)length;
                    NameNode *filter = dynamic_cast<NameNode *>(map->Get("/Filter"));
                    if (filter && filter->Name() == "/FlateDecode")
                    {
                        uncompressed = FlatDecode(stream, length, total);
                        delete [] stream;
                    }
                    else if (not filter)
                    {
                        uncompressed = stream;
                    }
                    else
                    {
                        wstring msg = L"compression not supported: ";
                        msg+= SingleToWide(filter->Name());
                        ErrorMessage(msg);
                        return;
                    }
                    stringstream stream_value;
                    stream_value.write(uncompressed, (streamsize)total);
                    stream_value.seekg(0);
                    delete [] uncompressed;

                    Scanner *temp = m_scanner;
                    m_scanner = new Scanner
                    { &stream_value };

                    vector<int> ids;
                    int loop;
                    for (loop = 0; loop < qtd; loop++)
                    {
                        nextToken();
                        ids.push_back((int) m_token->toNumber());
                        nextToken();
                    }
                    nextToken();
                    vector<int>::iterator id;
                    for (id = ids.begin(); id < ids.end(); id++)
                    {
                        ObjNode *new_obj = new ObjNode(*id, 0);
                        new_obj->SetValue(valueSequence());
                        root_node->AddChild(new_obj);
                    }
                    m_scanner = temp;
                }
            }
        }
    }
}

void Parser::commentSequence()
{
    m_scanner->ignoreLine();
    nextToken();
}

TreeNode *Parser::xrefSequence()
{
    XREFNode *xref = new XREFNode;
    match(TokenType::XREF);

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
        xref->AddNode(id, generation, address, name.at(0));
        id++;
    }
    
    match(TokenType::TRAILER);
    xref->SetTrailer(valueSequence());
    return xref;
}

void Parser::startXrefSequence()
{
    match(TokenType::START_XREF);
    match(TokenType::NUM);

    match(TokenType::PERCENT);
    match(TokenType::PERCENT);
    match(TokenType::END_PDF);
}

TreeNode *Parser::objectSequence()
{
    double number = m_token->toNumber();
    match(TokenType::NUM);
    double generation_nunber = m_token->toNumber();
    match(TokenType::NUM);

    ObjNode *node = new ObjNode((int) number, (int) generation_nunber);
    match(TokenType::OBJ);
    node->SetValue(valueSequence());
    if (m_token && m_token->type() == TokenType::STREAM)
    {
        int length = -1;
        MapNode *map = dynamic_cast<MapNode *>(node->Value());
        if (map)
        {
            NumberNode *numberNode = dynamic_cast<NumberNode *>(map->Get("/Length"));
            if (numberNode)
            {
                length = (int) numberNode->Value();
            }
        }
        node->SetStreamPos(m_scanner->ignoreStream(length));
        nextToken();
        match(TokenType::END_STREAM);
    }
    match(TokenType::END_OBJ);

    return node;
}

bool Parser::verifyVersion()
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
