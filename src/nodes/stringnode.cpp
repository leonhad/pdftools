#include "stringnode.h"

using namespace std;
using namespace node;

StringNode::StringNode(string value) noexcept : TreeNode()
{
    m_value = value;
}

string StringNode::value() const noexcept
{
    return m_value;
}
