#include "namenode.h"

using namespace std;
using namespace node;

NameNode::NameNode(std::string name) noexcept : TreeNode()
{
    m_name = name;
}

string NameNode::name() const noexcept
{
    return m_name;
}
