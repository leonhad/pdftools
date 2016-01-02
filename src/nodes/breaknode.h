#ifndef BREAKNODE_H
#define BREAKNODE_H

#include "treenode.h"

class BreakNode : public TreeNode {
public:
    BreakNode() noexcept;
    virtual ~BreakNode() noexcept = default;
};

#endif
