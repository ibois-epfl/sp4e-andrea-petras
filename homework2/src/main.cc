#include <iostream>
#include <cmath>

#include "series.hh"
#include "compute_arithmetic.hh"
#include "compute_pi.hh"

int main(int argc, char** argv)
{
    // Exo 2.3-4
    SCPP::ComputeArithmetic ca;
    std::cout << ca.compute(10) << std::endl;

    // Exo 2.5
    SCPP::ComputePi cp;
    std::cout << cp.compute(10) << std::endl;

    return 0;
}