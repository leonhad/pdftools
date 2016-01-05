#ifndef ARRAYNODE_H
#define ARRAYNODE_H

#include "treenode.h"
#include <vector>
#include <cstddef>

namespace node {

    class ArrayNode : public TreeNode {
    private:
        std::vector<TreeNode *> m_values;

    public:
        ArrayNode() noexcept;
        virtual ~ArrayNode() noexcept;

        void push(TreeNode *value) noexcept;
        TreeNode *value(size_t index) const noexcept;
        size_t size() const noexcept;
    };

}

#endif
