#include "write_series.hh"
#include <iostream>
#include <string>
#include <fstream>

namespace SCPP
{
    WriteSeries::WriteSeries(double frequency, double maxiter, Series& series)
        : DumperSeries(series), Frequency(frequency), Maxiter(maxiter)
    {};

    void WriteSeries::dump() 
    {
        std::string path = "../series.txt";
        std::ofstream file;
        file.open(path.c_str(), std::ofstream::out | std::ofstream::trunc);

        if (std::isnan(p_Series.getAnalyticPrediction()))
        {
            file << "Analytic prediction not available" << std::endl;
        }
        else
        {
            file << "Analytic prediction: " << p_Series.getAnalyticPrediction() << std::endl;
        }
        for (double i = 0; i < Maxiter; i += Frequency)
        {
            file << "Term " << i << ": " << p_Series.compute(i) << std::endl;
        }
        file.flush();
        file.close();
    };
}