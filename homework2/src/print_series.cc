#include "print_series.hh"
#include <iostream>

namespace SCPP
{
    PrintSeries::PrintSeries(double frequency, double maxiter, Series& series)
        : DumperSeries(series), Frequency(frequency), Maxiter(maxiter)
    {};

    void PrintSeries::dump(std::ostream& os) 
    {
        if (std::isnan(p_Series.getAnalyticPrediction()))
        {
            os << "Analytic prediction not available" << std::endl;
        }
        else
        {
            os << "Analytic prediction: " << p_Series.getAnalyticPrediction() << std::endl;
        }

        for (double i = 0; i < Maxiter; i += Frequency)
        {
            os << "Term " << i << ": " << p_Series.compute(i) << std::endl;
        }
    };
}