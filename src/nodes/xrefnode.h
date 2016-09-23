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
