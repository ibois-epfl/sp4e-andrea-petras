#include "riemann_integral.hh"
#include <iostream>
#include <cmath>
#include <limits>

namespace SCPP
{
    RiemannIntegral::RiemannIntegral(double a, double b, std::function <double(double)> f)
        : m_a(a), m_b(b), m_f(f)
    {};

    double RiemannIntegral::compute(unsigned int N)
    {
        double sum = 0.0;
        double delta = (m_b - m_a) / N;
        CurrentIndex = 1;

        while (std::abs(m_ExpectedValue - CurrentValue) > 0.01)
        {
            CurrentValue = sum;
            sum += m_f(m_a + CurrentIndex * delta) * delta;
            CurrentIndex++;
        }
        return CurrentValue;
    };
}