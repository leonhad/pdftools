#include "textnode.h"

using namespace std;
using namespace node;

TextNode::TextNode() noexcept : TreeNode()
{
}

void TextNode::add(string text) noexcept
{
    m_value += text;
}

string TextNode::text() const noexcept
{
    return m_value;
}
