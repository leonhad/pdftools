#ifndef OBJNODE_H
#define OBJNODE_H

#include "treenode.h"
#include <vector>
#include <cstdint>
#include <cstddef>

namespace node {

    class ObjNode : public TreeNode {
    private:
        int m_id;
        int m_generation;
        size_t m_stream_pos;
        TreeNode *m_value = nullptr;

    public:
        ObjNode(int id, int generation) noexcept;
        virtual ~ObjNode() noexcept;

        void set_value(TreeNode *value) noexcept;
        void set_stream_pos(size_t pos) noexcept;

        int id() const noexcept;
        int generation() const noexcept;
        size_t stream_pos() const noexcept;
        TreeNode *value() const noexcept;
        bool this_object(int id, int generation) const noexcept;
        void clear_stream() noexcept;
    };

}

#endif
