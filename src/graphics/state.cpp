#include "state.h"

State::State() noexcept
{
    reset();
}

double State::get_text_font() const noexcept
{
    return m_text_matrix[1][1];
}

void State::set_text_matrix(double a, double b, double c, double d, double e, double f) noexcept
{
    m_text_matrix[0][0] = a;
    m_text_matrix[0][1] = b;
    m_text_matrix[1][0] = c;
    m_text_matrix[1][1] = d;
    m_text_matrix[2][0] = e;
    m_text_matrix[2][1] = f;
}

void State::reset() noexcept
{
    m_text_matrix[0][0] = 1;
    m_text_matrix[0][1] = 0;
    m_text_matrix[0][2] = 0;
    m_text_matrix[1][0] = 0;
    m_text_matrix[1][1] = 1;
    m_text_matrix[1][2] = 0;
    m_text_matrix[2][0] = 0;
    m_text_matrix[2][1] = 0;
    m_text_matrix[2][2] = 1;
}
