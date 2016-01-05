#ifndef REFNODE_H
#define REFNODE_H

#include "treenode.h"

namespace node {

    class RefNode : public TreeNode {
    private:
        int m_id;
        int m_generation;

    public:
        RefNode(int id, int generation) noexcept;
        virtual ~RefNode() noexcept = default;

        int id() const noexcept;
        int generation() const noexcept;
    };

}

#endif
