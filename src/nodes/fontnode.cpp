#include "fontnode.h"

using namespace std;
using namespace node;

FontNode::FontNode() noexcept : TreeNode()
{
}

string FontNode::name() const noexcept
{
    return m_name;
}

int FontNode::size() const noexcept
{
    return m_size;
}

void FontNode::set_name(string name) noexcept
{
    m_name = name;
}

void FontNode::set_size(int size) noexcept
{
    m_size = size;
}
