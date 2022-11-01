#pragma once

#include "series.hh"
#include "dumper_series.hh"
#include <ostream>
#include <iostream>
#include <string>

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
        virtual void dump(std::ostream& os = std::cout) override;  // FIXME: find better design than default std::cout as parameter

        /// @brief change file format 
        /// @param separator: ',' = .csv, ' ' = .txt, '\t' = .txt, '|' = .psv
        void SetSeparator(char separator);
    
    public:
        double Frequency;
        double Maxiter;
    
    private:
        std::string m_Ending;
    };
}