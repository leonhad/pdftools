#include <stdexcept>
#include <vector>
#include "mapnode.h"
#include "treenode.h"

using namespace std;

MapNode::MapNode() noexcept : TreeNode()
{
}

MapNode::~MapNode() noexcept
{
    auto i = m_values.begin();
    while (i != m_values.end()) {
        delete (*i).second;
        i++;
    }
}

TreeNode *MapNode::get(string name) const noexcept
{
    try {
        return m_values.at(name);
    } catch (out_of_range &) {
        return nullptr;
    }
}

vector<string> MapNode::names() const noexcept
{
    vector<string> names;
    auto i = m_values.begin();
    while (i != m_values.end()) {
        names.push_back((*i).first);
        i++;
    }
    return names;
}

map<string, TreeNode *> MapNode::values() const noexcept
{
    return m_values;
}

void MapNode::push(string name, TreeNode *value) noexcept
{
    m_values[name] = value;
}
