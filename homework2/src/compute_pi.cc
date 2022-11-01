#include "compute_pi.hh"
#include <cmath>

namespace SCPP
{
    double ComputePi::compute(unsigned int N)
    {
        double pi = 0.0;
        for (int k = 1; k <= N; k++)
        {
            pi += 1.0 / (k * k);
        }
        pi = std::sqrt(6.0 * pi);
        return pi;
    };

    double ComputePi::getAnalyticPrediction()
    {
        return M_PI;
    }
}