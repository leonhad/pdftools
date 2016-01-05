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
