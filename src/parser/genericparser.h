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
#ifndef GENERICPARSER_H
#define GENERICPARSER_H

#include "scanner.h"
#include <sstream>

namespace node {
    class TreeNode;
}

namespace parser {
    class GenericParser {
    protected:
        Scanner *m_scanner;
        Token *m_token = nullptr;
        
    public:
        GenericParser(std::istream *filein) noexcept;
        virtual ~GenericParser() noexcept;
        
    protected:
        node::TreeNode *value_sequence();
        bool match(TokenType type);
        void next_token();
    };
    
}

#endif
