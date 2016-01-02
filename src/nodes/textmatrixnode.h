#ifndef TEXTMATRIXNODE_H
#define TEXTMATRIXNODE_H

#include "treenode.h"

class TextMatrixNode : public TreeNode {
private:
    double m_a;
    double m_b;
    double m_c;
    double m_d;
    double m_e;
    double m_f;
    
public:
    TextMatrixNode(double a, double b, double c, double d, double e, double f) noexcept;
    virtual ~TextMatrixNode() noexcept = default;
    
    double a() const noexcept;
    double b() const noexcept;
    double c() const noexcept;
    double d() const noexcept;
    double e() const noexcept;
    double f() const noexcept;
};

#endif
