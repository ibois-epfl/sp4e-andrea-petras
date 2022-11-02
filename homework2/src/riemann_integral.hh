#pragma once

#include "series.hh"
#include <functional>

namespace SCPP
{
    class RiemannIntegral: public Series
    {
    public:
        RiemannIntegral(double a, double b, std::function <double(double)> f);

        double compute(unsigned int N) override;

        inline void setA(double a) { m_a = a; };
        inline void setB(double b) { m_b = b; };
        inline void setF(std::function <double(double)> f) { m_f = f; };

    private:
        double m_a;
        double m_b;
        std::function <double(double)> m_f;
    };
}