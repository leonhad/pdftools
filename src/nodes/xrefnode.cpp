#include "xrefnode.h"

using namespace std;

XREFNode::XREFNode() noexcept : TreeNode()
{
}

XREFNode::~XREFNode() noexcept
{
    if (m_trailer) {
        delete m_trailer;
    }
}

void XREFNode::set_trailer(TreeNode *trailer) noexcept
{
    m_trailer = trailer;
}

TreeNode *XREFNode::trailer() const noexcept
{
    return m_trailer;
}

void XREFNode::add_node(uint16_t id, uint16_t generation, uint32_t address, char status) noexcept
{
    object_reference xref;
    xref.id = id;
    xref.generation = generation;
    xref.address = address;
    xref.status = status;
    m_references.push_back(xref);
}
