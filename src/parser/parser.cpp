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
        NextToken();
    }
    else
    {
        throw GenericException("Invalid input file.");
    }
}

RootNode *Parser::Parse()
{
    RootNode *root = new RootNode();
    bool error = false;
    Match(TokenType::PERCENT);
    if (VerifyVersion())
    {
        while (m_scanner->Good() && not error)
        {
            switch (m_token->Type())
            {
            case TokenType::PERCENT:
                CommentSequence();
                break;
            case TokenType::NUM:
                root->AddChild(ObjectSequence());
                break;
            case TokenType::XREF:
                root->AddChild(XrefSequence());
                break;
            case TokenType::START_XREF:
                StartXrefSequence();
                break;
            default:
                NextToken();
                error = true;
                break;
            }
        }
    }
    else
    {
         throw GenericException("Invalid input file.");
    }
    m_scanner->Clear();
    ObjectStreams(root);
    return root;
}

void Parser::ObjectStreams(RootNode *root_node)
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

                    m_scanner->ToPos(root_object->StreamPos());
                    char *stream = m_scanner->Stream((streamsize)length);

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
                        NextToken();
                        ids.push_back((int) m_token->ToNumber());
                        NextToken();
                    }
                    NextToken();
                    vector<int>::iterator id;
                    for (id = ids.begin(); id < ids.end(); id++)
                    {
                        ObjNode *new_obj = new ObjNode(*id, 0);
                        new_obj->SetValue(ValueSequence());
                        root_node->AddChild(new_obj);
                    }
                    m_scanner = temp;
                }
            }
        }
    }
}

void Parser::CommentSequence()
{
    m_scanner->IgnoreLine();
    NextToken();
}

TreeNode *Parser::XrefSequence()
{
    XREFNode *xref = new XREFNode;
    Match(TokenType::XREF);

    uint16_t id = (uint16_t) m_token->ToNumber();
    Match(TokenType::NUM);
    int count = (int) m_token->ToNumber();
    Match(TokenType::NUM);

    for (int loop = 0; loop < count; loop++)
    {
        uint32_t address = (uint32_t) m_token->ToNumber();
        Match(TokenType::NUM);
        uint16_t generation = (uint16_t) m_token->ToNumber();
        Match(TokenType::NUM);
        string name = m_token->Value();
        if (m_token->Type() == TokenType::F_LO)
        {
            Match(TokenType::F_LO);
        }
        else
        {
            Match(TokenType::N);
        }
        xref->AddNode(id, generation, address, name.at(0));
        id++;
    }
    
    Match(TokenType::TRAILER);
    xref->SetTrailer(ValueSequence());
    return xref;
}

void Parser::StartXrefSequence()
{
    Match(TokenType::START_XREF);
    Match(TokenType::NUM);

    Match(TokenType::PERCENT);
    Match(TokenType::PERCENT);
    Match(TokenType::END_PDF);
}

TreeNode *Parser::ObjectSequence()
{
    double number = m_token->ToNumber();
    Match(TokenType::NUM);
    double generation_nunber = m_token->ToNumber();
    Match(TokenType::NUM);

    ObjNode *node = new ObjNode((int) number, (int) generation_nunber);
    Match(TokenType::OBJ);
    node->SetValue(ValueSequence());
    if (m_token && m_token->Type() == TokenType::STREAM)
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
        node->SetStreamPos(m_scanner->IgnoreStream(length));
        NextToken();
        Match(TokenType::END_STREAM);
    }
    Match(TokenType::END_OBJ);

    return node;
}

bool Parser::VerifyVersion()
{
    if (m_token)
    {
        string line = m_token->Value();
        if (pdf_versions(line))
        {
            Match(TokenType::NAME);
            return true;
        }
    }
    return false;
}
