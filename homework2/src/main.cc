#include <iostream>
#include <cmath>
#include <memory>
#include <sstream>

#include "series.hh"
#include "compute_arithmetic.hh"
#include "compute_pi.hh"
#include "print_series.hh"
#include "write_series.hh"

int main(int argc, char** argv)
{
    // Parse arguments
    std::stringstream convert;

    if (argc != 6 || std::string(argv[1]) == "help" || std::string(argv[1]) == "H" || std::string(argv[0]) == "h")
    {
        std::cout << "Usage: " << argv[0] << " <N> <series> <frequency> <maxiter> <printMode>" << std::endl;
        std::cout << "N: number of terms" << std::endl;
        std::cout << "series: arithmetic or pi" << std::endl;
        std::cout << "Frequency: step between two outputs" << std::endl;
        std::cout << "Maxiter: capping for steps" << std::endl;
        std::cout << "printMode: 0 to print on screen, 1 to print on file" << std::endl;
        return 1;
    }
    
    convert << argv[1] << " " << argv[2] << " " << argv[3] << " " << argv[4] << " " << argv[5];
    
    unsigned int N;
    std::string series;
    double frequency;
    double maxiter;
    unsigned int printMode;

    convert >> N >> series >> frequency >> maxiter >> printMode;

    // Allocate pointer but do not allocate memory
    std::unique_ptr<SCPP::Series> s;

    // Allocate memory and assign pointer
    if (series == "arithmetic")
    {
        s = std::make_unique<SCPP::ComputeArithmetic>();
    }
    else if (series == "pi")
    {
        s = std::make_unique<SCPP::ComputePi>();
    }
    else
    {
        std::cout << "Unknown series: " << series << std::endl;
        return 1;
    }

    // Print series on screen or in file
    if (printMode == 0)
    {
        SCPP::PrintSeries printer(frequency, maxiter, *s);
        printer.dump();
    }
    else if (printMode == 1)
    {
        SCPP::WriteSeries writer(frequency, maxiter, *s);
        writer.dump();
    }
    else
    {
        std::cout << "Unknown print mode: " << printMode << std::endl;
        return 1;
    }

    return 0;
}