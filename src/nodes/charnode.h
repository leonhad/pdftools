#ifndef CHARNODE_H
#define CHARNODE_H

#include "treenode.h"
#include <string>

namespace node {

    class CharNode : public TreeNode {
    private:
        std::string m_char;
        std::string m_unicode;

    public:
        CharNode(std::string character, std::string unicode) noexcept;
        virtual ~CharNode() noexcept = default;

        std::string character() const noexcept;
        std::string unicode() const noexcept;
    };

}

#endif
