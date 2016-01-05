#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "genericparser.h"
#include <string>
#include <fstream>
#include <stdexcept>

namespace node {
    class TreeNode;
    class RootNode;
}

namespace parser {
    
    class Parser : public GenericParser {
    private:
        bool m_linear;
        std::string m_version;
        
    public:
        Parser(std::ifstream *filein) throw(std::exception);
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
