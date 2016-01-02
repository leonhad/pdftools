#ifndef FONTNODE_H
#define FONTNODE_H

#include "treenode.h"
#include <string>

class FontNode : public TreeNode {
private:
    std::string m_name;
    int m_size;

public:
    FontNode() noexcept;
    virtual ~FontNode() noexcept = default;
    
    std::string name() const noexcept;
    int size() const noexcept;
    void set_name(std::string name) noexcept;
    void set_size(int size) noexcept;
};

#endif
