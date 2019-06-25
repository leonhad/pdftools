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
#include "utils.h"

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

bool GenericParser::match(TokenType type)
{
    if (m_token && m_token->type() == type)
    {
        nextToken();
    }
    else
    {
#ifdef DEBUG
        string msg = "unexpected token: ";
        if (m_token)
        {
            msg += m_token->value();
        }
        error_message(msg.c_str());
#endif
        nextToken();
        return false;
    }
    return true;
}

void GenericParser::nextToken()
{
    m_token = m_scanner->nextToken();
}

TreeNode *GenericParser::valueSequence()
{
    if (m_token->type() == TokenType::START_DICT)
    {
        match(TokenType::START_DICT);
        MapNode *map = new MapNode;

        while (m_scanner->good() && m_token && m_token->type() != TokenType::END_DICT)
        {
            string name = m_token->value();
            match(TokenType::NAME);
            TreeNode *value = valueSequence();
            NameNode *n = dynamic_cast<NameNode *>(value);
            if (n && n->name() [0] != '/')
            {
                value = valueSequence();
            }
            map->push(name, value);
        }
        match(TokenType::END_DICT);
        return map;
    }
    else if (m_token->type() == TokenType::TRUE)
    {
        match(TokenType::TRUE);
        return new BooleanNode(true);
    }
    else if (m_token->type() == TokenType::FALSE)
    {
        match(TokenType::FALSE);
        return new BooleanNode(false);
    }
    else if (m_token->type() == TokenType::NAME)
    {
        string name = m_token->value();
        match(TokenType::NAME);
        return new NameNode(name);
    }
    else if (m_token->type() == TokenType::STRING)
    {
        string value = m_token->value();
        match(TokenType::STRING);
        return new StringNode(value);
    }
    else if (m_token->type() == TokenType::NUM)
    {
        double value = m_token->toNumber();
        size_t pos = m_scanner->pos();
        match(TokenType::NUM);

        if (m_token->type() == TokenType::NUM)
        {
            double generation = m_token->toNumber();
            match(TokenType::NUM);
            if (m_token->type() == TokenType::NAME && m_token->value() == "R")
            {
                match(TokenType::NAME);
                return new RefNode(value, generation);
            }
            else
            {
                m_scanner->to_pos(pos);
            }
        }
        else
        {
            m_scanner->to_pos(pos);
        }
        nextToken();
        return new NumberNode(value);
    }
    else if (m_token->type() == TokenType::START_ARRAY)
    {
        ArrayNode *array = new ArrayNode;
        match(TokenType::START_ARRAY);
        while (m_scanner->good() && m_token->type() != TokenType::END_ARRAY)
        {
            array->push(valueSequence());
        }
        match(TokenType::END_ARRAY);
        return array;
    }

    return nullptr;
}
