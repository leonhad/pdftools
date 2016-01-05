#include "genericexception.h"

using namespace std;

GenericException::GenericException(string msg) noexcept : m_msg{msg}
{
}

GenericException::GenericException(GenericException &&ex) noexcept : m_msg{move(ex.m_msg)}
{
}

const char *GenericException::what() const noexcept
{
    return m_msg.c_str();
}
