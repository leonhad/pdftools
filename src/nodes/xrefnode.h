#ifndef XREFNODE_H
#define XREFNODE_H

#include "treenode.h"
#include <vector>
#include <stdint.h>

namespace node {

    struct object_reference {
        uint32_t address;
        uint16_t id;
        uint16_t generation;
        char status;
    };

    class XREFNode : public TreeNode {
    private:
        std::vector<object_reference> m_references;
        TreeNode *m_trailer = nullptr;

    public:
        XREFNode() noexcept;
        virtual ~XREFNode() noexcept;

        void add_node(uint16_t id, uint16_t generation, uint32_t address, char status) noexcept;
        void set_trailer(TreeNode *trailer) noexcept;

        TreeNode *trailer() const noexcept;
    };

}

#endif
