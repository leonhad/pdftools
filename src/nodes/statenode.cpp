#include "statenode.h"

StateNode::StateNode(bool save) noexcept : TreeNode(), m_save{save}
{
}

bool StateNode::save() const  noexcept
{
    return m_save;
}
