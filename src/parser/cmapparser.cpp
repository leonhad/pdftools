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
#include "../nodes/nodes.h"
#include "../utils.h"
#include "scanner.h"
#include "cmapparser.h"

#include <cstring>

using namespace std;
using namespace parser;
using namespace node;

CMapParser::CMapParser(istream *stream) : GenericParser{stream}
{
    m_scanner->DisableCharsetConversion();
    m_root = nullptr;
}

std::shared_ptr<CMapNode> CMapParser::Parse()
{
    int val;

    m_root = make_shared<CMapNode>();

    NextToken();

    // /CIDInit
    Match(TokenType::NAME);
    // /ProcSet
    Match(TokenType::NAME);
    // find resource
    Match(TokenType::NAME);
    // begin
    Match(TokenType::NAME);
    // 12
    Match(TokenType::NUM);
    // dict
    Match(TokenType::NAME);
    // begin
    Match(TokenType::NAME);
    //begin cmap
    Match(TokenType::NAME);

    while (m_scanner->Good())
    {
        switch (m_token->Type())
        {
        case TokenType::NAME:
            if (m_token->Value() == "/CMapName")
            {
                Match(TokenType::NAME);
                // /Name
                Match(TokenType::NAME);
                // def
                Match(TokenType::NAME);
            }
            else if (m_token->Value() == "/CMapType")
            {
                Match(TokenType::NAME);
                // 2
                Match(TokenType::NUM);
                // def
                Match(TokenType::NAME);
            }
            else if (m_token->Value() == "/CIDSystemInfo")
            {
                Match(TokenType::NAME);
                auto value = ValueSequence();
                // Ignore the return.

                // def
                Match(TokenType::NAME);
            }
            else
            {
                Match(TokenType::NAME);
            }
            break;
        case TokenType::NUM:
            val = (int)m_token->ToNumber();
            Match(TokenType::NUM);
            if (m_token->Value() == "beginbfchar")
            {
                Match(TokenType::NAME);
                BfCharSequence(val);
            }
            else if (m_token->Value() == "begincodespacerange")
            {
                Match(TokenType::NAME);
                m_root->SetCodeSpace(CodeSpaceSequence());
            }
            else if (m_token->Value() == "beginbfrange")
            {
                Match(TokenType::NAME);
                BfRangeSequence(val);
            }
            else
            {
                Match(TokenType::NAME);
                ErrorMessage(L"invalid mode");
            }
            break;
        default:
            NextToken();
            break;
        }
    }
    return m_root;
}

std::shared_ptr<CodeSpaceNode> CMapParser::CodeSpaceSequence()
{
    auto ret = make_shared<CodeSpaceNode>();
    ret->SetStart(m_token->Value());
    Match(TokenType::STRING);
    ret->SetFinish(m_token->Value());
    Match(TokenType::STRING);
    // end code space range
    Match(TokenType::NAME);
    return ret;
}

void CMapParser::BfCharSequence(const int count)
{
    for (int loop = 0; loop < count; loop++)
    {
        string character = m_token->Value();
        Match(TokenType::STRING);
        string unicode = m_token->Value();
        Match(TokenType::STRING);
        m_root->Add(make_shared<CharNode>(character, unicode));
    }
    Match(TokenType::NAME);
}

void CMapParser::BfRangeSequence(const int count)
{
    for (int loop = 0; loop < count; loop++)
    {
        string start = m_token->Value();
        Match(TokenType::STRING);
        string end = m_token->Value();
        Match(TokenType::STRING);
        std::shared_ptr<TreeNode> node = ValueSequence();
        if (const auto name = std::dynamic_pointer_cast<StringNode>(node))
        {
            // FIXME fix this mess.

            char* chars = const_cast<char*>(start.c_str());
            char* b = chars;
            b++;
            const size_t size = start.size();

            while (strcmp(chars, end.c_str()) <= 0)
            {
                m_root->Add(make_shared<CharNode>(string(chars, size), name->Value()));
                if (size == 1)
                {
                    (*chars)++;
                }
                else
                {
                    uint16_t c = static_cast<uint16_t>(*chars << 8) + (*b & 255);
                    c++;
                    *chars = c >> 8;
                    *b = static_cast<char>(c & 0xFF);
                }
            }
        }
        else
        {
            ErrorMessage(L"test map");
            const auto array = std::dynamic_pointer_cast<ArrayNode>(node);
            auto chars = const_cast<char*>(start.c_str());
            const size_t size = start.size();
            size_t loop2 = 0;

            while (memcmp(chars, end.c_str(), size) < 0)
            {
                const auto name = std::dynamic_pointer_cast<StringNode>(array->Value(loop2));
                m_root->Add(make_shared<CharNode>(string(chars, size), name->Value()));
                if (size == 1)
                {
                    (*chars)++;
                }
                else
                {
                    auto* c = reinterpret_cast<uint16_t*>(chars);
                    (*c)++;
                }

                loop2++;
            }
        }
    }

    Match(TokenType::NAME);
}
