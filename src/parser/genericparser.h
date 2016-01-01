#ifndef GENERICPARSER_H
#define GENERICPARSER_H

#include "scanner.h"

class TreeNode;

namespace parser {
    class GenericParser {
    protected:
        Scanner m_scanner;
        Token *m_token = nullptr;
        
    public:
        GenericParser() = default;
        virtual ~GenericParser() = default;
        
    protected:
        TreeNode *value_sequence();
        bool match(TokenType type);
        void next_token();
    };
    
}

#endif
