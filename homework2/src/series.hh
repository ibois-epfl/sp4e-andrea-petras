#pragma once

namespace SCPP
{
    class Series
    {
    public:
        /// @brief compute the Nth term of the series
        /// @param N number of terms
        /// @return the result of the series as double
        virtual double compute(unsigned int N) = 0;
    };
}
