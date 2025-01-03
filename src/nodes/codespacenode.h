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
#include <string>

namespace node
{
    /**
     * Stores a code space node.
     */
    class CodeSpaceNode final : public TreeNode
    {
        /**
         * The code space start.
         */
        std::string m_start;

        /**
         * The code space finish.
         */
        std::string m_finish;

    public:
        /**
         * Creates a new instance.
         */
        CodeSpaceNode() = default;

        /**
         * Destroy this instance.
         */
        ~CodeSpaceNode() override = default;

        /**
         * Sets the code space start.
         *
         * @param start the code space start.
         */
        void SetStart(const std::string& start);

        /**
         * Sets the code space finish.
         *
         * @param finish the code space finish.
         */
        void SetFinish(const std::string& finish);

        /**
         * Gets the code space start.
         *
         * @return the code space start.
         */
        [[nodiscard]] std::string Start() const;

        /**
         * Gets the code space finish.
         *
         * @return the code space finish.
         */
        [[nodiscard]] std::string Finish() const;
    };
}
