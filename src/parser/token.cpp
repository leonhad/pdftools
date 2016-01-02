#include "token.h"
#include <cstdlib>

using namespace std;

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
    return atof(m_value.c_str());
}

string Token::value() const noexcept
{
    return m_value;
}

TokenType Token::type() const noexcept
{
    return m_type;
}
