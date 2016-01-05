#include "booleannode.h"

using namespace node;

BooleanNode::BooleanNode(bool value) noexcept
{
    m_value = value;
}

bool BooleanNode::value() const noexcept
{
    return m_value;
}
