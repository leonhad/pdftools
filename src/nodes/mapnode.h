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
#ifndef MAPNODE_H
#define MAPNODE_H

#include "treenode.h"
#include <map>
#include <string>
#include <vector>

namespace node
{

/**
 * Stores a map node.
 */
class MapNode: public TreeNode
{
private:
    /**
     * Stores a map of nodes.
     */
    std::map<std::string, TreeNode *> values;

public:
    /**
     * Creates a new instance.
     */
    MapNode();

    /**
     * Destroy this instance.
     */
    virtual ~MapNode();

    /**
     * Pushes a value to this map.
     *
     * @param name the node name.
     * @param value the node value.
     */
    void Push(std::string name, TreeNode *value);

    /**
     * Gets the map of tree node values.
     *
     * @return the map of tree node values.
     */
    std::map<std::string, TreeNode *> Values() const;

    /**
     * Gets the node names.
     *
     * @return the node names.
     */
    std::vector<std::string> Names() const;

    /**
     * Gets a map by its name.
     *
     * @param name the node name.
     * @return the node.
     */
    TreeNode *Get(std::string name) const;
};
}

#endif
