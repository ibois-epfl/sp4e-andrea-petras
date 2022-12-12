#include "compute_temperature.hh"
#include "fft.hh"
#include "material_point.hh"
#include <cmath>

/* -------------------------------------------------------------------------- */

void ComputeTemperature::compute(System& system)
{
    // Implement a solver of the transient heat equation in two dimensions as such:
    // rho C(del theta)/(del t)-kappa((del^(2)theta)/(delx^(2))+(del^(2)theta)/(dely^(2)))=h_(v)
    // where p is the mass density, C is the specific heat capacity, k is the thermal conductivity,
    // hv is the volumetric heat source, and theta is unkown and it is the temperature.

    // (a) Set the parameters
    uint N = std::sqrt(system.getNbParticles());

    Matrix<complex> mIn(N);
    Matrix<complex> mOut(N);
    Matrix<complex> hvIn(N);
    Matrix<complex> hvOut(N);

    Matrix<complex> interimThetaA(N);
    Matrix<complex> interimTheta;  ///< interimTheta = (rho*C)/(kappa*dt)

    // (b) Initialize the temperature and the heat rate
    for (auto&& entry : index(mIn))
    {
        int i, j;
        i = std::get<0>(entry);
        j = std::get<1>(entry);
        complex& val = std::get<2>(entry);

        // get the temperature and the heat source
        mIn(i, j) = static_cast<MaterialPoint&>(system.getParticle(i * N + j)).getTemperature();
        hvIn(i, j) = static_cast<MaterialPoint&>(system.getParticle(i * N + j)).getHeatRate();

        // check for particles on the boundary conditions of temperature
        if (i == 0 || i == N - 1 || j == 0 || j == N - 1)
        {
            static_cast<MaterialPoint&>(system.getParticle(i * N + j)).setBoundary(true);
        }
    }

    // (c) Perform the Fourier transform
    hvOut = FFT::transform(hvIn);
    mOut = FFT::transform(mIn);

    // (d) Solve the heat equation in Fourier space
    Matrix<std::complex<int>> freq = FFT::computeFrequencies(N);
    for (uint j = 0; j<N; j++)
    {
        for (uint i = 0; i<N; i++){
            double coeff = 2. * M_PI / this->m_DomSize;
            double q = pow(coeff * freq(i, j).real(), 2) + pow(coeff * freq(i, j).imag(), 2);
            interimThetaA(i, j) = 1.0 / (this->m_MassDensity * this->m_HeatCapacity)
                                  * (hvOut(i, j) 
                                  - this->m_HeatConductivity * mOut(i, j)*q);
        }
    }

    // (e) Invert transform
    interimTheta = FFT::itransform(interimThetaA);

    // (f) Updates the variable members of the particles
    for (auto&& entry : index(interimTheta))
    {
        int i, j;
        i = std::get<0>(entry);
        j = std::get<1>(entry);
        auto& mp = static_cast<MaterialPoint&>(system.getParticle(i * N + j));
        if (mp.isAtBoundary())
        {
            mp.setTemperature(0.0);
        }
        else
        {
            mp.getTemperature() 
            += this->m_DomSize * interimTheta(i,j).real();
        }
        
    }
}
/* -------------------------------------------------------------------------- */
