#include "refnode.h"

using namespace node;

RefNode::RefNode(int id, int generation) noexcept : TreeNode()
{
    m_id = id;
    m_generation = generation;
}

int RefNode::id() const noexcept
{
    return m_id;
}

int RefNode::generation() const noexcept
{
    return m_generation;
}
