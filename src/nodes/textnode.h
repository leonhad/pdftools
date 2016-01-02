#ifndef TEXTNODE_H
#define TEXTNODE_H

#include "treenode.h"
#include <string>

using namespace std;

class TextNode : public TreeNode {
private:
    string m_value;
    
public:
    TextNode() noexcept;
    virtual ~TextNode() noexcept = default;
    
    void add(string text) noexcept;
    string text() const noexcept;
};

#endif
