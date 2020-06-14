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
#ifndef NUMBERNODE_H
#define NUMBERNODE_H

#include "treenode.h"

namespace node
{
    /**
     * Stores a number node.
     */
    class NumberNode: public TreeNode
    {
    private:
        /**
         * The number value.
         */
        double m_value;

    public:
        /**
         * Creates a new instance.
         *
         * @param value the number value.
         */
        explicit NumberNode(double value);

        /**
         * Destroy this instance.
         */
        virtual ~NumberNode() override = default;

        /**
         * Gets the number value.
         * @return the number value.
         */
        double Value() const;
    };
}

#endif
