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
#ifndef NAMENODE_H
#define NAMENODE_H

#include "treenode.h"
#include <string>

namespace node
{
    /**
     * Stores a name node.
     */
    class NameNode: public TreeNode
    {
    private:
        /**
         * The name.
         */
        std::string name;

    public:
        /**
         * Creates a new instance.
         *
         * @param name the name.
         */
        explicit NameNode(const std::string &name);

        /**
         * Destroy this instance.
         */
        virtual ~NameNode() override = default;

        /**
         * Gets the name.
         *
         * @return the name.
         */
        std::string Name() const;
    };
}

#endif
