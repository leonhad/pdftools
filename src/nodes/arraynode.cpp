#include "arraynode.h"

using namespace std;

ArrayNode::ArrayNode() noexcept : TreeNode()
{
}

ArrayNode::~ArrayNode() noexcept
{
    for (auto &i : m_values) {
        delete i;
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
