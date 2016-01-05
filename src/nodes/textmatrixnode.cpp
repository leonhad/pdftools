#include "textmatrixnode.h"

using namespace node;

TextMatrixNode::TextMatrixNode(double a, double b, double c, double d, double e, double f) noexcept : TreeNode()
{
    m_a = a;
    m_b = b;
    m_c = c;
    m_d = d;
    m_e = e;
    m_f = f;
}

double TextMatrixNode::a() const noexcept
{
    return m_a;
}

double TextMatrixNode::b() const noexcept
{
    return m_b;
}

double TextMatrixNode::c() const noexcept
{
    return m_c;
}

double TextMatrixNode::d() const noexcept
{
    return m_d;
}

double TextMatrixNode::e() const noexcept
{
    return m_e;
}

double TextMatrixNode::f() const noexcept
{
    return m_f;
}
