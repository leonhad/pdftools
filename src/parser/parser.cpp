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
#include <fstream>

using namespace std;
using namespace parser;
using namespace node;

inline bool pdf_versions(string const& version)
{
    return version == "PDF-1.1" || version == "PDF-1.2" || version == "PDF-1.3"
        || version == "PDF-1.4" || version == "PDF-1.5" || version == "PDF-1.6"
        || version == "PDF-1.7";
}

Parser::Parser(ifstream *filein) : GenericParser{filein}
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

std::shared_ptr<RootNode> Parser::Parse()
{
    std::shared_ptr<RootNode> root(new RootNode());
    Match(TokenType::PERCENT);
    if (VerifyVersion())
    {
        bool error = false;
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

void Parser::ObjectStreams(const std::shared_ptr<RootNode>& root_node)
{
    const size_t size = root_node->Size();

    for (size_t i = 0; i < size; i++)
    {
        if (const auto root_object = std::dynamic_pointer_cast<ObjNode>(root_node->Get(i)))
        {
            if (const auto map = std::dynamic_pointer_cast<MapNode>(root_object->Value()))
            {
                const auto type = std::dynamic_pointer_cast<NameNode>(map->Get("/Type"));
                if (type && type->Name() == "/ObjStm")
                {
                    int qtd = 0;
                    size_t length = 0;
                    if (const auto number = std::dynamic_pointer_cast<NumberNode>(map->Get("/N")))
                    {
                        qtd = static_cast<int>(number->Value());
                    }

                    if (const auto length_node = std::dynamic_pointer_cast<NumberNode>(map->Get("/Length")))
                    {
                        length = static_cast<size_t>(length_node->Value());
                    }
                    const char* uncompressed = nullptr;

                    m_scanner->ToPos(root_object->StreamPos());
                    const string stream = m_scanner->Stream(static_cast<streamsize>(length));

                    size_t total = length;
                    if (const auto filter = std::dynamic_pointer_cast<NameNode>(map->Get("/Filter")); filter && filter->Name() == "/FlateDecode")
                    {
                        uncompressed = FlatDecode(stream.c_str(), length, total);
                    }
                    else if (not filter)
                    {
                        uncompressed = stream.c_str();
                    }
                    else
                    {
                        wstring msg = L"compression not supported: ";
                        msg += SingleToWide(filter->Name());
                        ErrorMessage(msg);
                        return;
                    }
                    stringstream stream_value;
                    stream_value.write(uncompressed, static_cast<streamsize>(total));
                    stream_value.seekg(0);
                    delete [] uncompressed;

                    const shared_ptr<Scanner> temp = m_scanner;
                    m_scanner = make_shared<Scanner>(&stream_value);

                    vector<int> ids;
                    for (int loop = 0; loop < qtd; loop++)
                    {
                        NextToken();
                        ids.push_back(static_cast<int>(m_token->ToNumber()));
                        NextToken();
                    }
                    NextToken();

                    for (const auto id : ids)
                    {
                        const auto new_obj = make_shared<ObjNode>(id, 0);
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

std::shared_ptr<TreeNode> Parser::XrefSequence()
{
    std::shared_ptr<XREFNode> xref(new XREFNode);
    Match(TokenType::XREF);

    auto id = static_cast<uint16_t>(m_token->ToNumber());
    Match(TokenType::NUM);
    const auto count = static_cast<int>(m_token->ToNumber());
    Match(TokenType::NUM);

    for (int loop = 0; loop < count; loop++)
    {
        const auto address = static_cast<uint32_t>(m_token->ToNumber());
        Match(TokenType::NUM);
        const auto generation = static_cast<uint16_t>(m_token->ToNumber());
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

std::shared_ptr<TreeNode> Parser::ObjectSequence()
{
    const double number = m_token->ToNumber();
    Match(TokenType::NUM);
    const double generation_number = m_token->ToNumber();
    Match(TokenType::NUM);

    const auto node = make_shared<ObjNode>(static_cast<int>(number), static_cast<int>(generation_number));
    Match(TokenType::OBJ);
    node->SetValue(ValueSequence());
    if (m_token && m_token->Type() == TokenType::STREAM)
    {
        int length = -1;
        if (const auto map = std::dynamic_pointer_cast<MapNode>(node->Value()))
        {
            if (const auto numberNode = std::dynamic_pointer_cast<NumberNode>(map->Get("/Length")))
            {
                length = static_cast<int>(numberNode->Value());
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
        if (const string line = m_token->Value(); pdf_versions(line))
        {
            Match(TokenType::NAME);
            return true;
        }
    }

    return false;
}
