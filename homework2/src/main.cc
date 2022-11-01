#include <iostream>
#include <cmath>
#include <memory>

#include "series.hh"
#include "compute_arithmetic.hh"
#include "compute_pi.hh"
#include "print_series.hh"

int main(int argc, char** argv)
{
    /* Exo 2.5 */

    // Parse arguments
    if (argc != 3 || std::string(argv[1]) == "help" || std::string(argv[1]) == "H" || std::string(argv[0]) == "h")
    {
        std::cout << "Usage: " << argv[0] << " <N> <series>" << std::endl;
        std::cout << "N: number of terms" << std::endl;
        std::cout << "series: arithmetic or pi" << std::endl;
        return 1;
    }

    unsigned int N = std::stoi(argv[1]);
    std::string series = argv[2];

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

    // Compute and print result
    double result = s->compute(N);
    std::cout << "Result of " << series << " series: " << result << std::endl;

    // Exo 3.1-2-3
    SCPP::PrintSeries ps = SCPP::PrintSeries(1, 10, *s);
    ps.dump();

    return 0;
}