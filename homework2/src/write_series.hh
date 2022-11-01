#pragma once
#include "series.hh"
#include "dumper_series.hh"

namespace SCPP
{
    class WriteSeries: public DumperSeries
    {
    public:
        /// @brief output (to a file) every step out of frequency that is lower than maxiter.
        /// @param frequency: step between two outputs
        /// @param maxiter: maximum number of terms to output
        /// @param series: series to compute each step
        WriteSeries(double frequency, double maxiter, Series& series);

        /// @brief output (to a file) every step out of frequency that is lower than maxiter.
        virtual void dump() override;
    
    public:
        double Frequency;
        double Maxiter;
    };
}