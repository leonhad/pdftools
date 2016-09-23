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
#include "token.h"

using namespace std;
using namespace parser;

Token::Token() noexcept
{
}

Token::~Token() noexcept
{
}

void Token::set_value(string value) noexcept
{
    m_value = value;
}

void Token::set_type(TokenType type) noexcept
{
    m_type = type;
}

double Token::to_number() const noexcept
{
    return stof(m_value);
}

string Token::value() const noexcept
{
    return m_value;
}

TokenType Token::type() const noexcept
{
    return m_type;
}
