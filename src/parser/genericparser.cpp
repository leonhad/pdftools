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

GenericParser::GenericParser(std::istream* filein) :
    m_scanner(new Scanner(filein)), m_token(nullptr)
{
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
    m_token = make_shared<Token>(m_scanner->NextToken());
}

std::shared_ptr<TreeNode> GenericParser::ValueSequence()
{
    if (m_token->Type() == TokenType::START_DICT)
    {
        Match(TokenType::START_DICT);
        std::shared_ptr<MapNode> map(new MapNode());

        while (m_scanner->Good() && m_token && m_token->Type() != TokenType::END_DICT)
        {
            string name = m_token->Value();
            Match(TokenType::NAME);
            auto value = ValueSequence();

            if (const auto n = std::dynamic_pointer_cast<NameNode>(value); n && n->Name()[0] != '/')
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
        return make_shared<BooleanNode>(true);
    }
    else if (m_token->Type() == TokenType::FALSE)
    {
        Match(TokenType::FALSE);
        return make_shared<BooleanNode>(false);
    }
    else if (m_token->Type() == TokenType::NAME)
    {
        const string name = m_token->Value();
        Match(TokenType::NAME);
        return make_shared<NameNode>(name);
    }
    else if (m_token->Type() == TokenType::STRING)
    {
        const string value = m_token->Value();
        Match(TokenType::STRING);
        return make_shared<StringNode>(value);
    }
    else if (m_token->Type() == TokenType::NUM)
    {
        const double value = m_token->ToNumber();
        const streampos pos = m_scanner->Pos();
        Match(TokenType::NUM);

        if (m_token->Type() == TokenType::NUM)
        {
            int generation = m_token->ToInt();
            Match(TokenType::NUM);
            if (m_token->Type() == TokenType::NAME && m_token->Value() == "R")
            {
                Match(TokenType::NAME);
                return make_shared<RefNode>(value, generation);
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
        return make_shared<NumberNode>(value);
    }
    else if (m_token->Type() == TokenType::START_ARRAY)
    {
        const std::shared_ptr<ArrayNode> array(new ArrayNode);
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
