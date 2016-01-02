#ifndef BOOLEANNODE_H
#define BOOLEANNODE_H

#include "treenode.h"

class BooleanNode : public TreeNode {
private:
    bool m_value;

public:
    BooleanNode(bool value) noexcept;
    virtual ~BooleanNode() noexcept = default;

    bool value() const noexcept;
};

#endif
