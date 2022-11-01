#include <iostream>
#include <cmath>
#include <memory>
#include <sstream>
#include <fstream>

#include "series.hh"
#include "compute_arithmetic.hh"
#include "compute_pi.hh"
#include "print_series.hh"
#include "write_series.hh"

int main(int argc, char** argv)
{
    // Parse arguments
    std::stringstream convert;

    if (argc != 7 || std::string(argv[1]) == "help" || std::string(argv[1]) == "H" || std::string(argv[0]) == "h")
    {
        std::cout << "Usage: " << argv[0] << " <N> <series> <frequency> <maxiter> <printMode> <fileformat>" << std::endl;
        std::cout << "N: number of terms" << std::endl;
        std::cout << "series: arithmetic or pi" << std::endl;
        std::cout << "Frequency: step between two outputs" << std::endl;
        std::cout << "Maxiter: capping for steps" << std::endl;
        std::cout << "printMode: 0 to print on screen, 1 to print on file" << std::endl;
        std::cout << "separator: the format output file ',' = .csv, ' ' = .txt, '\t' = .txt, '|' = .psv" << std::endl;
        return 1;
    }
    
    convert << argv[1] << " " << argv[2] << " " << argv[3] << " " << argv[4] << " " << argv[5] << " " << argv[6];
    
    unsigned int N;
    std::string series;
    double frequency;
    double maxiter;
    unsigned int printMode;
    char separator;

    convert >> N >> series >> frequency >> maxiter >> printMode >> separator;

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
    std::ofstream os;
    SCPP::PrintSeries p(frequency, maxiter, *s);
    SCPP::WriteSeries w(frequency, maxiter, *s);
    w.SetSeparator(separator);

    if (printMode == 1)
    {
        os << w;
    }
    else
    {
        std::cout << p;
    }

    return 0;
}