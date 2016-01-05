#include "objnode.h"
#include <cstdlib>

using namespace std;
using namespace node;

ObjNode::ObjNode(int id, int generation) noexcept : TreeNode(), m_id{id}, m_generation{generation}
{
}

ObjNode::~ObjNode() noexcept
{
    if (m_value) {
        delete m_value;
    }
}

int ObjNode::id() const noexcept
{
    return m_id;
}

int ObjNode::generation() const noexcept
{
    return m_generation;
}

TreeNode *ObjNode::value() const noexcept
{
    return m_value;
}

bool ObjNode::this_object(int id, int generation) const noexcept
{
    return m_id == id && m_generation == generation;
}

void ObjNode::set_value(TreeNode *value) noexcept
{
    if (m_value) {
        delete m_value;
    }
    m_value = value;
}

void ObjNode::set_stream_pos(size_t pos) noexcept
{
    m_stream_pos = pos;
}

size_t ObjNode::stream_pos() const noexcept
{
    return m_stream_pos;
}
