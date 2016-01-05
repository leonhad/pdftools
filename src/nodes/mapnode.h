#ifndef MAPNODE_H
#define MAPNODE_H

#include "treenode.h"
#include <map>
#include <string>
#include <vector>

namespace node {

    class MapNode : public TreeNode {
    private:
        std::map<std::string, TreeNode *> m_values;

    public:
        MapNode() noexcept;
        virtual ~MapNode() noexcept;

        void push(std::string name, TreeNode *value) noexcept;
        std::map<std::string, TreeNode *> values() const noexcept;
        std::vector<std::string> names() const noexcept;

        TreeNode *get(std::string name) const noexcept;
    };

}

#endif
