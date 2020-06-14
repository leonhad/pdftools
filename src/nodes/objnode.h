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
#ifndef OBJNODE_H
#define OBJNODE_H

#include "treenode.h"
#include <vector>
#include <cstdint>
#include <cstddef>
#include <istream>

namespace node
{
    /**
     * Stores a object node.
     */
    class ObjNode: public TreeNode
    {
    private:
        /**
         * The object id.
         */
        int m_id;

        /**
         * The object generation.
         */
        int m_generation;

        /**
         * The binary object stream position.
         */
        std::streampos m_streamPos;

        /**
         * The tree node value.
         */
        TreeNode *m_value;

    public:
        /**
         * Creates a new instance.
         *
         * @param id the object id.
         * @param generation the object generation.
         */
        ObjNode(int id, int generation);

        /**
         * Destroy this instance.
         */
        virtual ~ObjNode() override;

        /**
         * Sets the tree node value.
         *
         * @param value the tree node value.
         */
        void SetValue(TreeNode *value);

        /**
         * Sets the binary stream position.
         *
         * @param pos the binary stream position.
         */
        void SetStreamPos(std::streampos pos);

        /**
         * Gets the object id.
         *
         * @return the object id.
         */
        int Id() const;

        /**
         * Gets the object generation.
         *
         * @return the object generation.
         */
        int Generation() const;

        /**
         * Gets the binary stream position.
         *
         *@return the binary stream position.
         */
        std::streampos StreamPos() const;

        /**
         * Gets the tree node value.
         *
         * @return the tree node value.
         */
        TreeNode *Value() const;

        /**
         * Check if the references is this object.
         *
         * @param id the object id.
         * @param generation the object generation.
         * @return true if the references is this object.
         */
        bool SameObject(int id, int generation) const;
    };
}

#endif
