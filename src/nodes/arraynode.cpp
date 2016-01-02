#include "arraynode.h"

using namespace std;

ArrayNode::ArrayNode() noexcept : TreeNode()
{
}

ArrayNode::~ArrayNode() noexcept
{
    auto i = m_values.begin();
    while (i != m_values.end()) {
        delete *i;
        i++;
    }
}

TreeNode *ArrayNode::value(size_t index) const noexcept
{
    return m_values[index];
}

size_t ArrayNode::size() const noexcept
{
    return m_values.size();
}

void ArrayNode::push(TreeNode *value) noexcept
{
    m_values.push_back(value);
}
