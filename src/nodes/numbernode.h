#ifndef NUMBERNODE_H
#define NUMBERNODE_H

#include "treenode.h"

class NumberNode : public TreeNode {
private:
    double m_value;

public:
    NumberNode(double value) noexcept;
    virtual ~NumberNode() noexcept = default;
    
    double value() const noexcept;
};

#endif
