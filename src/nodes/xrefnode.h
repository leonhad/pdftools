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
#ifndef XREFNODE_H
#define XREFNODE_H

#include "treenode.h"
#include <vector>
#include <stdint.h>

namespace node
{
    /**
     * A XREF object reference.
     */
    class ObjectReference
    {
    public:
        /**
         * PDF object address.
         */
        uint32_t address;

        /**
         * PDF object ID.
         */
        uint16_t id;

        /**
         * PDF object genetarion.
         */
        uint16_t generation;

        /**
         * Object status.
         */
        char status;
    };

    /**
     * Stotes a XREF node.
     */
    class XREFNode : public TreeNode
    {
    private:
        /**
         * A list of all object references.
         */
        std::vector<ObjectReference> m_references;

        /**
         * The tree node trailer.
         */
        TreeNode *m_trailer;

    public:
        /**
         * Creates a new instance.
         */
        XREFNode();

        /**
         * Destroy this instance.
         */
        virtual ~XREFNode();

        /**
         * Add a node to this XREF.
         *
         * \param id the object ID.
         * \param generation the object generation.
         * \param address the object address.
         * \param status the object status.
         */
        void addNode(uint16_t id, uint16_t generation, uint32_t address, char status);

        /**
         * Sets the trailer node.
         *
         * \param trailer the trailer node to set.
         */
        void setTrailer(TreeNode *trailer);

        /**
         * Gets the the tree node trailer.
         * \return the tree node trailer.
         */
        TreeNode *trailer() const;
    };
}

#endif
