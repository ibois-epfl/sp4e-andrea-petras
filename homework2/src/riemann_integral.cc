#include "riemann_integral.hh"
#include <iostream>

namespace SCPP
{
    RiemannIntegral::RiemannIntegral(double a, double b, std::function <double(double)> f)
        : m_a(a), m_b(b), m_f(f)
    {};

    double RiemannIntegral::compute(unsigned int N)
    {
        double sum = 0.0;
        double h = (m_b - m_a) / N;
        CurrentIndex = 1;
        for (unsigned int i = 1; sum < m_b; i++)
        {
            CurrentValue = sum;
            sum += m_f(m_a + i * h);
            CurrentIndex = i;
        }
        return CurrentValue;
    };
}