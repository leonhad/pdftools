#ifndef STATE_H
#define STATE_H

class State {
private:
    double m_text_matrix[3][3];

public:
    State() noexcept;
    ~State() noexcept = default;

    void reset() noexcept;
    void set_text_matrix(double a, double b, double c, double d, double e, double f) noexcept;
    double get_text_font() const noexcept;
};

#endif
