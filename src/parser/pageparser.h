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
#ifndef PAGEPARSER_H
#define PAGEPARSER_H

#include "genericparser.h"
#include <vector>

namespace node
{
    class BDCNode;

    class RootNode;

    class TreeNode;

    class Token;
}

namespace parser
{
    /**
     * Parses a PDF page.
     */
    class PageParser : public GenericParser
    {
    private:
        /**
         * The tree root node.
         */
        std::shared_ptr<node::RootNode> m_root = nullptr;

    public:
        /**
         * Create a new instance.
         *
         * @param stream the object stream.
         */
        explicit PageParser(std::istream *stream);

        /**
         * Destroy this instance.
         */
        ~PageParser() = default;

        /**
         * Parses the page.
         *
         * @return the root node.
         */
        std::shared_ptr<node::RootNode> Parse();

    private:
        /**
         * Parses the TM sequence.
         *
         * @param values the nodes to parse.
         * @return the sequence node.
         */
        std::shared_ptr<node::TreeNode> TmSequence(const std::vector<std::shared_ptr<node::TreeNode>>& values);

        /**
         * Parses the font sequence.
         *
         * @param values the nodes to parse.
         * @return the sequence node.
         */
        std::shared_ptr<node::TreeNode> FontSequence(const std::vector<std::shared_ptr<node::TreeNode>>& values);

        /**
         * Parses the BI sequence.
         *
         * @return the node.
         */
        std::shared_ptr<node::TreeNode> BiSequence();

        /**
         * Parses the TM sequence.
         *
         * @param values the nodes to parse.
         * @param parent the parent node.
         * @return the sequence node.
         */
        std::shared_ptr<node::BDCNode> BdcSequence(std::vector<std::shared_ptr<node::TreeNode>>& values,
                                                   const std::shared_ptr<node::RootNode>& parent);

        /**
         * Parses the text sequence.
         *
         * @param values the nodes to parse.
         * @return the sequence node.
         */
        static std::shared_ptr<node::TreeNode> TextSequence(const std::vector<std::shared_ptr<node::TreeNode>>& values);

        /**
         * Parses the TJUP node.
         *
         * @param root the root node.
         * @param values the node values.
         */
        void TjupSequence(const std::shared_ptr<node::RootNode>& root, const std::vector<std::shared_ptr<node::TreeNode>>& values);
    };
}

#endif
