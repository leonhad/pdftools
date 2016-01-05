#include "statenode.h"

using namespace node;

StateNode::StateNode(bool save) noexcept : TreeNode(), m_save{save}
{
}

bool StateNode::save() const  noexcept
{
    return m_save;
}
