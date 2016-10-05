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

#include "scanner.h"
#include "genericparser.h"
#include <istream>
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
        node::RootNode *m_root = nullptr;

    public:
        /**
         * Create a new instance.
         *
         * \param stream the object stream.
         */
        explicit PageParser(std::istream *stream);

        /**
         * Destroy this instance.
         */
        ~PageParser();

        /**
         * Parses the page.
         *
         * \return the root node.
         */
        node::RootNode *parse();

    private:
        /**
         * Parses the TM sequence.
         *
         * \param values the nodes to parse.
         * \return the sequence node.
         */
        node::TreeNode *tmSequence(std::vector<node::TreeNode *> &values);

        /**
         * Parses the font sequence.
         *
         * \param values the nodes to parse.
         * \return the sequence node.
         */
        node::TreeNode *fontSequence(std::vector<node::TreeNode *> &values);

        /**
         * Parses the BI sequence.
         *
         * \return the node.
         */
        node::TreeNode *biSequence();

        /**
         * Parses the TM sequence.
         *
         * \param values the nodes to parse.
         * \param parent the parent node.
         * \return the sequence node.
         */
        node::BDCNode *bdcSequence(std::vector<node::TreeNode *> &values, node::RootNode *parent);

        /**
         * Parses the text sequence.
         *
         * \param values the nodes to parse.
         * \return the sequence node.
         */
        node::TreeNode *textSequence(std::vector<node::TreeNode *> &values);

        /**
         * Parses the TJUP node.
         *
         * \param root the root node.
         * \param values the node values.
         */
        void tjupSequence(node::RootNode *root, std::vector<node::TreeNode *> &values);
    };
}

#endif
