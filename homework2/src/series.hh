#pragma once

#include <cmath>

namespace SCPP
{
    class Series
    {
    public:
        Series() = default;
        virtual ~Series() = default;

        /// @brief compute the Nth term of the series
        /// @param N number of terms
        /// @return the result of the series as double
        // virtual double compute(unsigned int N) = 0;
        virtual double compute(unsigned int N) = 0;

        /// @brief provides the analytic prediction of a class, by default returns NaN
        virtual double getAnalyticPrediction() { return std::nan("0"); };

    public:
        unsigned int CurrentIndex = 0;
        double CurrentValue = 0.0;
    };
}
