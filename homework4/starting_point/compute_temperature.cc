#include "compute_temperature.hh"
#include "fft.hh"
#include "material_point.hh"
#include <cmath>

/* -------------------------------------------------------------------------- */

void ComputeTemperature::compute(System& system) {

  UInt size = system.getNbParticles();
  UInt N = std::sqrt(size);
  Matrix<complex> temperature(N);
  Matrix<complex> heat_source(N);

  std::transform(system.begin(), system.end(), temperature.begin(),
                 [](auto& part) {
                   return static_cast<MaterialPoint&>(part).getTemperature();
                 });

  std::transform(system.begin(), system.end(), heat_source.begin(),
                 [](auto& part) {
                   return static_cast<MaterialPoint&>(part).getHeatSource();
                 });

  auto freqs = FFT::computeFrequencies(N);
  auto h_hat = FFT::transform(heat_source);
  auto T_hat = FFT::transform(temperature);
  auto T_rate_hat = Matrix<complex>(N);

  const auto factor = delta_t * density / capacity;
  const auto factor2 = 1. / density / capacity;

  auto implicit_integrator = [&](auto&& entry) {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& T_rate = std::get<2>(entry);
    auto f = freqs(i, j);
    Real k2 = std::abs(complex(f.real(), f.imag())) * 2. * M_PI / L;
    k2 *= k2;

    const auto factor2 = 1. + factor * conductivity * k2;

    T_rate_hat(i, j) =
        1. / factor2 * (factor * h_hat(i, j) + T_hat(i, j)) - T_hat(i, j);
  };

  auto explicit_integrator = [&](auto&& entry) {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& T_rate = std::get<2>(entry);
    auto f = freqs(i, j);
    Real k2 = std::abs(complex(f.real(), f.imag())) * 2. * M_PI / L;
    k2 *= k2;

    T_rate_hat(i, j) =
        1. / factor2 * (h_hat(i, j) + T_hat(i, j) * conductivity * k2);
  };

  if (implicit)
    for (auto entry : index(T_rate_hat))
      implicit_integrator(entry);

  else
    for (auto entry : index(T_rate_hat))
      explicit_integrator(entry);

  auto temperature_rate = FFT::itransform(T_rate_hat);
  auto it_temp_rate = temperature_rate.begin();
  for (auto& part : system) {
    auto& p = static_cast<MaterialPoint&>(part);

    p.getTemperatureRate() = (*it_temp_rate).real();
    p.getTemperature() += delta_t * p.getTemperatureRate();
    ++it_temp_rate;
  }
}

/* -------------------------------------------------------------------------- */
