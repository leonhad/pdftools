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
#include "genericparser.h"
#include "../nodes/nodes.h"
#include "../utils.h"

using namespace std;
using namespace parser;
using namespace node;

GenericParser::GenericParser(std::istream *filein) :
        m_scanner(new Scanner(filein)), m_token(nullptr)
{
}

GenericParser::~GenericParser()
{
    if (m_scanner)
    {
        delete m_scanner;
    }
}

bool GenericParser::Match(TokenType type)
{
    if (m_token && m_token->Type() == type)
    {
        NextToken();
    }
    else
    {
#ifdef DEBUG
        wstring msg = L"unexpected token: ";
        if (m_token)
        {
            msg += SingleToWide(m_token->Value());
        }
        ErrorMessage(msg);
#endif
        NextToken();
        return false;
    }
    return true;
}

void GenericParser::NextToken()
{
    m_token = m_scanner->NextToken();
}

TreeNode *GenericParser::ValueSequence()
{
    if (m_token->Type() == TokenType::START_DICT)
    {
        Match(TokenType::START_DICT);
        MapNode *map = new MapNode;

        while (m_scanner->Good() && m_token && m_token->Type() != TokenType::END_DICT)
        {
            string name = m_token->Value();
            Match(TokenType::NAME);
            TreeNode *value = ValueSequence();
            
            NameNode *n = dynamic_cast<NameNode *>(value);
            if (n && n->Name() [0] != '/')
            {
                value = ValueSequence();
            }
            
            map->Put(name, value);
        }
        Match(TokenType::END_DICT);
        return map;
    }
    else if (m_token->Type() == TokenType::TRUE)
    {
        Match(TokenType::TRUE);
        return new BooleanNode(true);
    }
    else if (m_token->Type() == TokenType::FALSE)
    {
        Match(TokenType::FALSE);
        return new BooleanNode(false);
    }
    else if (m_token->Type() == TokenType::NAME)
    {
        string name = m_token->Value();
        Match(TokenType::NAME);
        return new NameNode(name);
    }
    else if (m_token->Type() == TokenType::STRING)
    {
        string value = m_token->Value();
        Match(TokenType::STRING);
        return new StringNode(value);
    }
    else if (m_token->Type() == TokenType::NUM)
    {
        double value = m_token->ToNumber();
        streampos pos = m_scanner->Pos();
        Match(TokenType::NUM);

        if (m_token->Type() == TokenType::NUM)
        {
            int generation = m_token->ToInt();
            Match(TokenType::NUM);
            if (m_token->Type() == TokenType::NAME && m_token->Value() == "R")
            {
                Match(TokenType::NAME);
                return new RefNode((int)value, generation);
            }
            else
            {
                m_scanner->ToPos(pos);
            }
        }
        else
        {
            m_scanner->ToPos(pos);
        }
        NextToken();
        return new NumberNode(value);
    }
    else if (m_token->Type() == TokenType::START_ARRAY)
    {
        ArrayNode *array = new ArrayNode;
        Match(TokenType::START_ARRAY);
        while (m_scanner->Good() && m_token->Type() != TokenType::END_ARRAY)
        {
            array->Push(ValueSequence());
        }
        Match(TokenType::END_ARRAY);
        return array;
    }

    return nullptr;
}
