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
#ifndef TEXTMATRIXNODE_H
#define TEXTMATRIXNODE_H

#include "treenode.h"
#include <vector>
#include <initializer_list>

namespace node
{
    /**
     * Stores a text matrix node.
     */
    class TextMatrixNode : public TreeNode
    {
    private:
        /**
         * Matrix nodes.
         */
        std::vector<double> values;

    public:
        /**
         * Creates a new instance.
         *
         * \param list the list values.
         */
        explicit TextMatrixNode(const std::initializer_list<double> &list);

        /**
         * Destroy this instance.
         */
        virtual ~TextMatrixNode() = default;

        /**
         * Get a text matrix value by its index.
         *
         * \param index the index.
         * \return  the text matrix value.
         */
        double at(int index) const;
    };
}

#endif
