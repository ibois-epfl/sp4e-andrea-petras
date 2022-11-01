#pragma once

#include "series.hh"
#include "dumper_series.hh"
#include <iostream>
#include <ostream>

namespace SCPP
{
    class PrintSeries: public DumperSeries
    {
    public:
        /// @brief output (to screen) every step out of frequency that is lower than maxiter.
        /// @param frequency: step between two outputs
        /// @param maxiter: maximum number of terms to output
        /// @param series: series to compute each step
        PrintSeries(double frequency, double maxiter, Series& series);

        /// @brief output (to screen) every step out of frequency that is lower than maxiter.
        virtual void dump(std::ostream& os = std::cout) override;

    public:
        double Frequency;
        double Maxiter;
    };
}