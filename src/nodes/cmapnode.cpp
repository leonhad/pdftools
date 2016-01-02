#include "cmapnode.h"
#include "codespacenode.h"
#include "charnode.h"

using namespace std;

CMapNode::CMapNode() noexcept : TreeNode()
{
}

CMapNode::~CMapNode() noexcept
{
    vector<CharNode *>::iterator i;
    for (i = m_charnodes.begin(); i != m_charnodes.end(); i++) {
        delete *i;
    }
    if (m_codespace) {
        delete m_codespace;
    }
}

void CMapNode::add(CharNode *node) noexcept
{
    m_charnodes.push_back(node);
}

void CMapNode::set_codespace(CodeSpaceNode *codespace) noexcept
{
    m_codespace = codespace;
}

CodeSpaceNode *CMapNode::code_space() const noexcept
{
    return m_codespace;
}

size_t CMapNode::nodes() const noexcept
{
    return m_charnodes.size();
}

CharNode *CMapNode::node(size_t index) const noexcept
{
    return m_charnodes.at(index);
}
