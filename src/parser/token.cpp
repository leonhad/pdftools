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
