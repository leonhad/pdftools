#ifndef STRINGNODE_H
#define STRINGNODE_H

#include "treenode.h"
#include <string>

namespace node {

    class StringNode : public TreeNode {
    private:
        std::string m_value;

    public:
        StringNode(std::string value) noexcept;
        virtual ~StringNode() noexcept = default;

        std::string value() const noexcept;
    };

}

#endif
