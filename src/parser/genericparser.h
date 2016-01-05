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
