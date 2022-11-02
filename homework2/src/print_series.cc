#include "print_series.hh"
#include <iostream>

namespace SCPP
{
    PrintSeries::PrintSeries(double frequency, double maxiter, Series& series)
        : DumperSeries(series), Frequency(frequency), Maxiter(maxiter)
    {};

    void PrintSeries::dump(std::ostream& os) 
    {
        os.precision(p_Precision);

        if (std::isnan(p_Series.getAnalyticPrediction()))
        {
            os << "Analytic prediction not available" << std::endl;
        }
        else
        {
            os << "Analytic prediction: " << p_Series.getAnalyticPrediction() << std::endl;
        }

        if (p_Series.CurrentValue == 0.0 && p_Series.CurrentIndex != 1)
        {
            os << "[INFO][PrintSeries.cc]: No computation done yet" << std::endl;

            for (double i = 0; i < Maxiter; i += Frequency)
            {
                os << "Term " << i << ": " << p_Series.compute(i) << std::endl;
            }
        }
        else
        {
            os << "[INFO][PrintSeries.cc]: Last computed term: " << p_Series.CurrentIndex << std::endl;
            os << "[INFO][PrintSeries.cc]: Last computed value: " << p_Series.CurrentValue << std::endl;
        }
    };
}