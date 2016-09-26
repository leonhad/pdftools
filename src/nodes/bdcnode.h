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
#ifndef BDCCOMMAND_H
#define BDCCOMMAND_H

#include "rootnode.h"
#include <string>

namespace node
{
    /**
     * Stores a BCD node.
     */
    class BDCNode : public RootNode
    {
    private:
        RootNode *m_parent;
        TreeNode *m_value;
        std::string m_name;

    public:
        /**
         * Create a new instance.
         * \param parent the parant node.
         */
        explicit BDCNode(RootNode *parent);

        ~BDCNode();

        TreeNode *value();

        RootNode *parent();

        std::string name();

        void setValue(TreeNode *value);

        void setName(std::string name);
    };
}

#endif
