#ifndef CMAPPARSER_H
#define CMAPPARSER_H

#include "scanner.h"
#include "genericparser.h"
#include <istream>

namespace node {
    class TreeNode;
    class CMapNode;
    class CodeSpaceNode;
}

namespace parser {
    
    class CMapParser : public GenericParser {
    private:
        node::CMapNode *m_root;
        
    public:
        CMapParser(std::istream *stream);
        virtual ~CMapParser();
        
        node::CMapNode *parse();
        
    private:
        void bfchar_sequence(const int count);
        void bfrange_sequence(const int count);
        node::CodeSpaceNode *codespace_sequence();
    };
    
}

#endif
