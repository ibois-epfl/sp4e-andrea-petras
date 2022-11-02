#include <iostream>
#include <cmath>
#include <memory>
#include <sstream>
#include <fstream>

#include "riemann_integral.hh"

int main(int argc, char** argv)
{
    // Parse arguments
    std::stringstream convert;

    if (argc != 4 ||
        std::string(argv[1]) == "help" ||
        std::string(argv[1]) == "H" ||
        std::string(argv[0]) == "h")
    {
        std::cout << "Usage: " << argv[0] << " <N> <a> <b>" << std::endl;
        std::cout << "N: number of terms" << std::endl;
        std::cout << "a: lower bound" << std::endl;
        std::cout << "b: upper bound" << std::endl;
        return 1;
    }
    
    convert << argv[1] << " " << argv[2] << " " << argv[3];
    
    unsigned int N;
    double a, b;

    convert >> N >> a >> b;

    // Exo 6
    SCPP::RiemannIntegral riemann1(0, 1, [](double x) { return x; });

    riemann1.setA(0);
    riemann1.setB(1);
    riemann1.setF([](double x) { return x * x * x; });
    std::cout << "Riemann Integral of x^3 from 0 to 1: " << riemann1.compute(N) << std::endl;

    riemann1.setA(0);
    riemann1.setB(M_PI);
    riemann1.setF([](double x) { return cos(x); });
    std::cout << "Riemann Integral of cos(x) from 0 to pi: " << riemann1.compute(N) << std::endl;

    riemann1.setA(0);
    riemann1.setB(M_PI/2);
    riemann1.setF([](double x) { return sin(x); });
    std::cout << "Riemann Integral of sin(x) from 0 to pi/2: " << riemann1.compute(N) << std::endl;

    return 0;
}