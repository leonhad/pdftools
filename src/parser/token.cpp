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
#include "token.h"

using namespace std;
using namespace parser;

void Token::SetValue(string value)
{
    m_value = value;
}

void Token::SetType(TokenType type)
{
    m_type = type;
}

double Token::ToNumber() const
{
    try
    {
        return stod(m_value);
    }
    catch (...)
    {
        return 0.0;
    }
}

int Token::ToInt() const
{
    try {
        return stoi(m_value);
    }
    catch(...)
    {
        return 0;
    }
}

string Token::Value() const
{
    return m_value;
}

TokenType Token::Type() const
{
    return m_type;
}
