#ifndef BDCCOMMAND_H
#define BDCCOMMAND_H

#include "rootnode.h"
#include <string>

namespace node {

    class BDCNode : public RootNode {
    private:
        RootNode *m_parent;
        TreeNode *m_value;
        std::string m_name;

    public:
        BDCNode(RootNode *parent);
        ~BDCNode();

        TreeNode *value();
        RootNode *parent();
        std::string name();
        void set_value(TreeNode *value);
        void set_name(std::string name);
    };

}

#endif
