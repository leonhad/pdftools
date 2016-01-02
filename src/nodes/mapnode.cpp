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
    for (auto &i : m_values) {
        delete i.second;
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
    names.reserve(m_values.size());
    transform(m_values.begin(), m_values.end(), back_inserter(names), [](auto &pair) {return pair.first;});
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
