#include "compute_arithmetic.hh"
#include <cmath>

namespace SCPP
{
    double ComputeArithmetic::compute(unsigned int N)
    {
        double sum = 0.0;
        for (int k = 1; k <= N; k++)
        {
            sum += k;
        }
        return sum;
    };
}