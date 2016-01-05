#ifndef NAMENODE_H
#define NAMENODE_H

#include "treenode.h"
#include <string>

namespace node {

    class NameNode : public TreeNode {
    private:
        std::string m_name;

    public:
        NameNode(std::string name) noexcept;
        virtual ~NameNode() noexcept = default;

        std::string name() const noexcept;
    };

}

#endif
