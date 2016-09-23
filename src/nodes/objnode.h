/*
 * PDF Tools.
 * Copyright (C) 2012-2016 Leonardo Alves da Costa
 * mailto:leonhad AT gmail DOT com
 *
 * SonarQube is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * SonarQube is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
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
