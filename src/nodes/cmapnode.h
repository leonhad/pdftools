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
#ifndef CMAPNODE_H
#define CMAPNODE_H

#include "treenode.h"
#include <vector>
#include <cstring>

namespace node {

    class CodeSpaceNode;
    class CharNode;

    class CMapNode : public TreeNode {
    private:
        std::vector<CharNode *> m_charnodes;
        CodeSpaceNode *m_codespace = nullptr;

    public:
        CMapNode() noexcept;
        ~CMapNode() noexcept;

        void add(CharNode *node) noexcept;
        void set_codespace(CodeSpaceNode *codespace) noexcept;

        CodeSpaceNode *code_space() const noexcept;
        size_t nodes() const noexcept;
        CharNode *node(size_t index) const noexcept;
    };

}

#endif
