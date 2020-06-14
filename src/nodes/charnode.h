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
#ifndef CHARNODE_H
#define CHARNODE_H

#include "treenode.h"
#include <string>

namespace node
{
    /**
     * Stores a char node.
     */
    class CharNode: public TreeNode
    {
    private:
        /**
         * This char.
         */
        std::string m_thisChar;

        /**
         * The unicode value.
         */
        std::string m_unicode;

    public:
        /**
         * Creates a new instance.
         *
         * @param character the char value.
         * @param unicode the unicode value.
         */
        CharNode(const std::string &character, const std::string &unicode);

        /**
         * Destroy the instance.
         */
        virtual ~CharNode() override = default;

        /**
         * Gets the char value.
         *
         * @return the char value.
         */
        std::string Character() const;

        /**
         * Gets the unicode value.
         *
         * @return the unicode value.
         */
        std::string Unicode() const;
    };
}

#endif
