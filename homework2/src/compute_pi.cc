#include "compute_pi.hh"
#include <cmath>

namespace SCPP
{
    double ComputePi::compute(unsigned int N)
    {
        double pi = 0.0;
        CurrentIndex = 1;
        for (int k = 1; k <= N; k++)
        {
            pi += 1.0 / (k * k);
            CurrentIndex = k;
        }
        CurrentValue = std::sqrt(6.0 * pi);
        return CurrentValue;
    };

    double ComputePi::getAnalyticPrediction()
    {
        return M_PI;
    }
}