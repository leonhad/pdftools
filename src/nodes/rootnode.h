#ifndef ROOTNODE_H
#define ROOTNODE_H

#include <vector>
#include "treenode.h"

class RootNode : public TreeNode {
private:
    std::vector<TreeNode *> m_child;

public:
    RootNode() noexcept;
    virtual ~RootNode() noexcept;
    
    void add_child(TreeNode *child) noexcept;
    TreeNode *get(size_t index) const noexcept;
    size_t size() const noexcept;
};

#endif
