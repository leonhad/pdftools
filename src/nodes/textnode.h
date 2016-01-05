#ifndef TEXTNODE_H
#define TEXTNODE_H

#include "treenode.h"
#include <string>

namespace node {

    class TextNode : public TreeNode {
    private:
        std::string m_value;

    public:
        TextNode() noexcept;
        virtual ~TextNode() noexcept = default;

        void add(std::string text) noexcept;
        std::string text() const noexcept;
    };

}

#endif
