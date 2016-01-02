#ifndef CMAPNODE_H
#define CMAPNODE_H

#include "treenode.h"
#include <vector>

class CodeSpaceNode;
class CharNode;

class CMapNode : public TreeNode {
private:
    std::vector<CharNode *> m_charnodes;
    CodeSpaceNode *m_codespace = nullptr;

public:
    CMapNode() noexcept;
    ~CMapNode() noexcept;
    
    void add(CharNode *node) noexcept;
    void set_codespace(CodeSpaceNode *codespace) noexcept;
    
    CodeSpaceNode *code_space() const noexcept;
    size_t nodes() const noexcept;
    CharNode *node(size_t index) const noexcept;
};

#endif
