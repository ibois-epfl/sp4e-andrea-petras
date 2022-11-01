#include "print_series.hh"
#include <iostream>

namespace SCPP
{
    PrintSeries::PrintSeries(double frequency, double maxiter, Series& series)
        : DumperSeries(series), Frequency(frequency), Maxiter(maxiter)
    {};

    void PrintSeries::dump() 
    {
        if (std::isnan(p_Series.getAnalyticPrediction()))
        {
            std::cout << "Analytic prediction not available" << std::endl;
        }
        else
        {
            std::cout << "Analytic prediction: " << p_Series.getAnalyticPrediction() << std::endl;
        }

        for (double i = 0; i < Maxiter; i += Frequency)
        {
            std::cout << "Term " << i << ": " << p_Series.compute(i) << std::endl;
        }
    };
}