/*
 * PDF Tools.
 * Copyright (C) 2012-2016 Leonardo Alves da Costa
 * mailto:leonhad AT gmail DOT com
 *
 * SonarQube is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * SonarQube is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
#include "nodes/nodes.h"
#include "utils.h"
#include "scanner.h"
#include "token.h"
#include "cmapparser.h"
#include <cstring>

using namespace std;
using namespace parser;
using namespace node;

CMapParser::CMapParser(istream *stream) : GenericParser{stream}
{
    m_scanner->disable_charset_conversion();
    m_root = nullptr;
}

CMapParser::~CMapParser()
{
    if (m_root)
    {
        delete m_root;
    }
}

CMapNode *CMapParser::parse()
{
    int val;

    if (m_root)
    {
        delete m_root;
    }
    m_root = new CMapNode();

    next_token();

    // /CIDInit
    match(TokenType::NAME);
    // /ProcSet
    match(TokenType::NAME);
    // findresource
    match(TokenType::NAME);
    // begin
    match(TokenType::NAME);
    // 12
    match(TokenType::NUM);
    // dict
    match(TokenType::NAME);
    // begin
    match(TokenType::NAME);
    //begincmap
    match(TokenType::NAME);

    while (m_scanner->good())
    {
        switch (m_token->type())
        {
        case TokenType::NAME:
            if (m_token->value() == "/CMapName")
            {
                match(TokenType::NAME);
                // /Name
                match(TokenType::NAME);
                // def
                match(TokenType::NAME);
            }
            else if (m_token->value() == "/CMapType")
            {
                match(TokenType::NAME);
                // 2
                match(TokenType::NUM);
                // def
                match(TokenType::NAME);
            }
            else if (m_token->value() == "/CIDSystemInfo")
            {
                match(TokenType::NAME);
                delete value_sequence();
                // def
                match(TokenType::NAME);
            }
            else
            {
                match(TokenType::NAME);
            }
            break;
        case TokenType::NUM:
            val = m_token->to_number();
            match(TokenType::NUM);
            if (m_token->value() == "beginbfchar")
            {
                match(TokenType::NAME);
                bfchar_sequence(val);
            }
            else if (m_token->value() == "begincodespacerange")
            {
                match(TokenType::NAME);
                m_root->setCodespace(codespace_sequence());
            }
            else if (m_token->value() == "beginbfrange")
            {
                match(TokenType::NAME);
                bfrange_sequence(val);
            }
            else
            {
                match(TokenType::NAME);
                error_message("invalid mode");
            }
            break;
        default:
            next_token();
            break;
        }
    }
    return m_root;
}

CodeSpaceNode *CMapParser::codespace_sequence()
{
    CodeSpaceNode *ret = new CodeSpaceNode;
    ret->setStart(m_token->value());
    match(TokenType::STRING);
    ret->setFinish(m_token->value());
    match(TokenType::STRING);
    // endcodespacerange
    match(TokenType::NAME);
    return ret;
}

void CMapParser::bfchar_sequence(const int count)
{
    for (int loop = 0; loop < count; loop++)
    {
        string character = m_token->value();
        match(TokenType::STRING);
        string unicode = m_token->value();
        match(TokenType::STRING);
        m_root->add(new CharNode(character, unicode));
    }
    match(TokenType::NAME);
}

void CMapParser::bfrange_sequence(const int count)
{
    for (int loop = 0; loop < count; loop++)
    {
        string start = m_token->value();
        match(TokenType::STRING);
        string end = m_token->value();
        match(TokenType::STRING);
        TreeNode *node = value_sequence();
        StringNode *name = dynamic_cast<StringNode *> (node);
        if (name)
        {
            char *chars = const_cast<char *> (start.c_str());
            char *b = chars;
            b++;
            size_t size = start.size();

            while (strcmp(chars, end.c_str()) <= 0)
            {
                m_root->add(new CharNode(string(chars, size), name->value()));
                if (size == 1)
                {
                    (*chars)++;
                }
                else
                {
                    uint16_t c = (*chars << 8) + (*b & 255);
                    c++;
                    *chars = c >> 8;
                    *b = c & 0xFF;
                }
            }
        }
        else
        {
            error_message("test map");
            ArrayNode *array = dynamic_cast<ArrayNode *> (node);
            char *chars = const_cast<char *> (start.c_str());
            size_t size = start.size();
            int loop2 = 0;

            while (memcmp(chars, end.c_str(), size) < 0)
            {
                name = dynamic_cast<StringNode *> (array->value(loop2));
                m_root->add(new CharNode(string(chars, size), name->value()));
                if (size == 1)
                {
                    (*chars)++;
                }
                else
                {
                    uint16_t *c = (uint16_t *) chars;
                    (*c)++;
                }
                loop2++;
            }
        }
    }
    match(TokenType::NAME);
}
