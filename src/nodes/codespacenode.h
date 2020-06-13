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
#ifndef CODESPACENODE_H
#define CODESPACENODE_H

#include "treenode.h"
#include <string>

namespace node
{
    /**
     * Stores a code space node.
     */
    class CodeSpaceNode: public TreeNode
    {
    private:
        /**
         * The code space start.
         */
        std::string start;

        /**
         * The code space finish.
         */
        std::string finish;

    public:
        /**
         * Creates a new instance.
         */
        CodeSpaceNode();

        /**
         * Destroy this instance.
         */
        virtual ~CodeSpaceNode() override = default;

        /**
         * Sets the code space start.
         *
         * @param start the code space start.
         */
        void SetStart(const std::string &start);

        /**
         * Sets the code space finish.
         *
         * @param finish the code space finish.
         */
        void SetFinish(const std::string &finish);

        /**
         * Gets the code space start.
         *
         * @return the code space start.
         */
        std::string Start() const;

        /**
         * Gets the code space finish.
         *
         * @return the code space finish.
         */
        std::string Finish() const;
    };
}

#endif
