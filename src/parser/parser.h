#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <fstream>
#include <stdexcept>
#include "token.h"
#include "genericparser.h"

class Scanner;
class TreeNode;
class RootNode;

namespace parser {
    
    class Parser : public GenericParser {
    private:
        bool m_linear;
        std::string m_version;
        
    public:
        Parser(std::ifstream *filein) throw(exception);
        virtual ~Parser() noexcept = default;
        
        RootNode *parse();
        
    private:
        bool verify_version();
        void object_streams(RootNode *root);
        void startxref_sequence();
        
        void comment_sequence();
        TreeNode *object_sequence();
        TreeNode *xref_sequence();
    };
    
}

#endif
