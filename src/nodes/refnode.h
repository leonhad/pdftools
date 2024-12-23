/*
 * PDF Tools.
 * Copyright (C) 2012-2016 Leonardo Alves da Costa
 * mailto:leonhad AT gmail DOT com
 *
 * PDF Tools is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * PDF Tools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
#pragma once

#include "treenode.h"

namespace node
{
    /**
     * Stores a reference node.
     */
    class RefNode final : public TreeNode
    {
        /**
         * The object id.
         */
        int m_id;

        /**
         * The object generation.
         */
        int m_generation;

    public:
        /**
         * Creates a new instance.
         *
         * @param id the object id.
         * @param generation the object generation.
         */
        RefNode(int id, int generation);

        /**
         * Destroy the instance.
         */
        ~RefNode() override = default;

        /**
         * Gets the object id.
         *
         * @return the object id.
         */
        [[nodiscard]] int Id() const;

        /**
         * Gets the generation.
         *
         * @return the generation.
         */
        [[nodiscard]] int Generation() const;
    };
}
