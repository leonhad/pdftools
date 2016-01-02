#include "rootnode.h"

using namespace std;

RootNode::RootNode() noexcept : TreeNode()
{
}

RootNode::~RootNode() noexcept
{
    for (auto &i : m_child) {
        delete i;
    }
}

void RootNode::add_child(TreeNode *child) noexcept
{
    m_child.push_back(child);
}

TreeNode *RootNode::get(size_t index) const noexcept
{
    return m_child[index];
}

size_t RootNode::size() const noexcept
{
    return m_child.size();
}
