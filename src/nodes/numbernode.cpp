#include "numbernode.h"

using namespace node;

NumberNode::NumberNode(double value) noexcept : TreeNode(), m_value{value}
{
}

double NumberNode::value() const noexcept
{
    return m_value;
}
