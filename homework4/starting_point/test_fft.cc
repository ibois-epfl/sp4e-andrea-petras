#include "compute_temperature.hh"
#include "csv_writer.hh"
#include "fft.hh"
#include "material_points_factory.hh"
#include "my_types.hh"
#include "vector.hh"
#include <gtest/gtest.h>
/*****************************************************************/
TEST(FFT, transform) {
  UInt N = 512;
  Matrix<complex> m(N);

  Real k = 2 * M_PI / N;
  for (auto&& entry : index(m)) {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& val = std::get<2>(entry);
    val = cos(k * i);
  }

  Matrix<complex> res = FFT::transform(m);

  for (auto&& entry : index(res)) {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& val = std::get<2>(entry);
    if (std::abs(val) > 1e-10)
      std::cout << i << "," << j << " = " << val << std::endl;

    if (i == 1 && j == 0)
      ASSERT_NEAR(std::abs(val), N * N / 2, 1e-10);
    else if (i == N - 1 && j == 0)
      ASSERT_NEAR(std::abs(val), N * N / 2, 1e-10);
    else
      ASSERT_NEAR(std::abs(val), 0, 1e-10);
  }
}
/*****************************************************************/

TEST(FFT, inverse_transform) {
  UInt N = 512;
  Matrix<complex> m(N);

  Real k = 2 * M_PI / N;
  for (auto&& entry : index(m)) {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    std::get<2>(entry) = 0.;
  }

  m(1, 0) = N * N / 2;
  m(N - 1, 0) = N * N / 2;

  for (auto&& entry : index(m)) {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& val = std::get<2>(entry);
    if (std::abs(val) > 1e-10)
      std::cout << i << "," << j << " = " << val << std::endl;
  }

  Matrix<complex> res = FFT::itransform(m);

  for (auto&& entry : index(res)) {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& val = std::get<2>(entry);

    if (std::abs(val.real() - cos(k * i)) > 1e-10)
      std::cout << i << "," << j << " = " << val.real() << " " << cos(k * i)
                << std::endl;

    ASSERT_NEAR(val.real(), cos(k * i), 1e-14);
    ASSERT_NEAR(val.imag(), 0, 1e-14);
  }
}
/*****************************************************************/

template <typename F1, typename F2>
System createSystem(UInt N, F1 temperature_functor, F2 heat_source_functor) {
  auto& factory = MaterialPointsFactory::getInstance();
  System system;

  for (UInt i = 0; i < N; ++i) {
    for (UInt j = 0; j < N; ++j) {
      // create particle
      auto p = factory.createParticle();
      auto& part = static_cast<MaterialPoint&>(*p);

      auto x = -1. + 2. * double(i) / N;
      auto y = -1. + 2. * double(j) / N;
      auto& pos = part.getPosition();
      pos[0] = x;
      pos[1] = y;
      pos[2] = 0;

      auto& temp = part.getTemperature();
      temp = temperature_functor(i, j, pos);
      auto& heat_source = part.getHeatSource();
      heat_source = heat_source_functor(i, j, pos);

      // add particle to system
      system.addParticle(std::move(p));
    }
  }
  return system;
}

ComputeTemperature makeCompute() {
  ComputeTemperature compute;
  compute.getConductivity() = 1.;
  compute.getL() = 2.;
  compute.getCapacity() = 1.;
  compute.getDensity() = 1.;
  compute.getDeltat() = 1.;
  return compute;
}

TEST(ComputeTemperature, heat_source_lines) {
  auto& factory = MaterialPointsFactory::getInstance();
  UInt N = 256;

  auto system = createSystem(
      N,
      [](UInt i, UInt j, auto& pos) {
        if (pos[0] <= -1. / 2.)
          return -pos[0] - 1.;
        else if (pos[0] > 1. / 2.)
          return -pos[0] + 1.;
        else
          return pos[0];
      },
      [&](UInt i, UInt j, auto& pos) {
        if (i == int(double(N) / 4.))
          return -double(N);
        if (i == int(3. * double(N) / 4.))
          return double(N);
        return 0.;
      });

  auto compute = makeCompute();

  // launch it twice since the analytical solution do
  // not account for discretization
  compute.compute(system);
  compute.compute(system);

  for (auto&& p : system) {
    auto& part = static_cast<MaterialPoint&>(p);
    ASSERT_NEAR(part.getTemperatureRate(), 0., 1e-5);
  }
}

TEST(ComputeTemperature, constant_temperature) {
  auto& factory = MaterialPointsFactory::getInstance();
  UInt N = 256;
  auto system = createSystem(
      N, [&](UInt i, UInt j, auto& pos) { return 1.; },
      [&](UInt i, UInt j, auto& pos) { return 0.; });

  auto compute = makeCompute();

  // launch it twice since the analytical solution do not account for
  // discretization
  compute.compute(system);
  compute.compute(system);

  for (auto&& p : system) {
    auto& part = static_cast<MaterialPoint&>(p);
    ASSERT_NEAR(part.getTemperatureRate(), 0., 1e-10);
  }
}
