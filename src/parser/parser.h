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
#ifndef PARSER_H
#define PARSER_H

#include "genericparser.h"
#include <string>

namespace node
{
    class TreeNode;
    class RootNode;
}

namespace parser
{
    /**
     * Parses a PDF file.
     */
    class Parser : public GenericParser
    {
    private:
        /**
         * If this is a linear file.
         */
        bool m_linear;

        /**
         * The PDF file version.
         */
        std::string m_version;

    public:
        /**
         * Creates a new instance.
         *
         * \@param filein the file to parse.
         */
        explicit Parser(std::ifstream *filein);

        /**
         * Destroy this instance.
         */
        ~Parser() = default;

        /**
         * Parses the root node.
         *
         * @return the root node.
         */
        std::shared_ptr<node::RootNode> Parse();

    private:
        /**
         * Verify the PDF version.
         *
         * @return true if this file is a valid version.
         */
        bool VerifyVersion();

        /**
         * Parses the object streams.
         *
         * @param root the root node to parse.
         */
        void ObjectStreams(const std::shared_ptr<node::RootNode>& root);

        /**
         * Parses the start XREF sequences.
         */
        void StartXrefSequence();

        /**
         * Parses the comment sequences.
         */
        void CommentSequence();

        /**
         * Parses the object sequences.
         *
         * @return the object node.
         */
        std::shared_ptr<node::TreeNode> ObjectSequence();

        /**
         * Parses the XREF sequences.
         *
         * @return the XREF node.
         */
        std::shared_ptr<node::TreeNode> XrefSequence();
    };
}

#endif
