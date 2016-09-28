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

#include "token.h"
#include "genericparser.h"
#include <string>
#include <fstream>
#include <stdexcept>

namespace node
{
    class TreeNode;
    class RootNode;
}

namespace parser
{

    class Parser : public GenericParser
    {
    private:
        bool m_linear;
        std::string m_version;

    public:
        Parser(std::ifstream *filein) throw (std::exception);
        virtual ~Parser() noexcept = default;

        node::RootNode *parse();

    private:
        bool verify_version();
        void object_streams(node::RootNode *root);
        void startxref_sequence();

        void comment_sequence();
        node::TreeNode *object_sequence();
        node::TreeNode *xref_sequence();
    };

}

#endif
