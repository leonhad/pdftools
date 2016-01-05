#ifndef CODESPACENODE_H
#define CODESPACENODE_H

#include "treenode.h"
#include <string>

namespace node {

    class CodeSpaceNode : public TreeNode {
    private:
        std::string m_start;
        std::string m_finish;

    public:
        CodeSpaceNode() noexcept;
        virtual ~CodeSpaceNode() noexcept = default;

        void set_start(std::string start) noexcept;
        void set_finish(std::string finish) noexcept;

        std::string start() const noexcept;
        std::string finish() const noexcept;
    };

}

#endif
