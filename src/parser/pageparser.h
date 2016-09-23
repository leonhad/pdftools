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
#ifndef PAGEPARSER_H
#define PAGEPARSER_H

#include "scanner.h"
#include "genericparser.h"
#include <istream>
#include <vector>

namespace node {
    class BDCNode;
    class RootNode;
    class TreeNode;
    class Token;
}

namespace parser {
    
    class PageParser: public GenericParser {
    private:
        node::RootNode *m_root = nullptr;
        
    public:
        PageParser(std::istream *stream);
        ~PageParser();
        
        node::RootNode *parse();
        
    private:
        node::TreeNode *tm_sequence(std::vector<node::TreeNode *> &values);
        node::TreeNode *font_sequence(std::vector<node::TreeNode *> &values);
        node::TreeNode *bi_sequence();
        node::BDCNode *bdc_sequence(std::vector<node::TreeNode *> &values, node::RootNode *parent);
        node::TreeNode *text_sequence(std::vector<node::TreeNode *> &values);
        void tjup_sequence(node::RootNode *root, std::vector<node::TreeNode *> &values);
        
    };
    
}

#endif
