#ifndef OBJNODE_H
#define OBJNODE_H

#include "treenode.h"
#include <vector>
#include <stdint.h>

using namespace std;

class ObjNode : public TreeNode {
private:
    int m_id;
    int m_generation;
    size_t m_stream_pos;
    TreeNode *m_value;
    
public:
    ObjNode(int id, int generation);
    virtual ~ObjNode();
    
    void set_value(TreeNode *value);
    void set_stream_pos(size_t pos);
    
    int id();
    int generation();
    size_t stream_pos();
    TreeNode *value();
    bool this_object(int id, int generation);
    void clear_stream();
};

#endif
