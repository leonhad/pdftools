#include "codespacenode.h"

using namespace std;
using namespace node;

CodeSpaceNode::CodeSpaceNode() noexcept : TreeNode()
{
}

void CodeSpaceNode::set_start(string start) noexcept
{
    m_start = start;
}

void CodeSpaceNode::set_finish(string finish) noexcept
{
    m_finish = finish;
}

string CodeSpaceNode::start() const noexcept
{
    return m_start;
}

string CodeSpaceNode::finish() const noexcept
{
    return m_finish;
}
