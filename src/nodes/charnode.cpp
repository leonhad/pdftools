#include "charnode.h"

using namespace std;

CharNode::CharNode(string character, string unicode) noexcept : TreeNode()
{
    m_char = character;
    m_unicode = unicode;
}

string CharNode::character() const noexcept
{
    return m_char;
}

string CharNode::unicode() const noexcept
{
    return m_unicode;
}
