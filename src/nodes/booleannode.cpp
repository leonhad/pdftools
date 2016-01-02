#include "booleannode.h"

BooleanNode::BooleanNode(bool value) noexcept
{
    m_value = value;
}

bool BooleanNode::value() const noexcept
{
    return m_value;
}
