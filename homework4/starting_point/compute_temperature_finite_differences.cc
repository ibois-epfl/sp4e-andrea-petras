#include "compute_temperature_finite_differences.hh"
#include "material_point.hh"
#include "matrix.hh"

void ComputeTemperatureFiniteDifferences::compute(System& system) {
  static bool should_factorize = true;

  if (should_factorize) {
    assembleLinearOperator(system);
    A.makeCompressed();
    solver.analyzePattern(A);
    solver.factorize(A);

    should_factorize = false;
  }

  auto N = system.getNbParticles();

  Eigen::VectorXd theta(N);

  assembleRightHandSide(system);
  theta = solver.solve(rhs);

  // Transferring temperature back
  auto it = theta.begin();
  for (auto& part : system) {
    static_cast<MaterialPoint&>(part).getTemperature() = (*it);
    ++it;
  }
}

void ComputeTemperatureFiniteDifferences::assembleLinearOperator(
    System& system) {
  UInt n = std::sqrt(system.getNbParticles());

  // Column major
  auto idx = [n](UInt i, UInt j) { return j * n + i; };

  for (UInt i = 0; i < n; ++i)
    for (UInt j = 0; j < n; ++j) {
      std::array<std::tuple<UInt, UInt, UInt>, 5> stencil = {
          std::make_tuple(i - 1, j, 1), std::make_tuple(i, j - 1, 1),
          std::make_tuple(i, j, -4), std::make_tuple(i + 1, j, 1),
          std::make_tuple(i, j + 1, 1)};
      auto k = idx(i, j);
      for (auto&& tup : stencil) {
        auto l = idx(std::get<0>(tup), std::get<1>(tup));
        A.coeffRef(k, l) -=
            std::get<2>(tup) * n * n * dt;  // 1/a^2 * dt / (rho*C)
      }
    }

  // Identity term in linear operator
  A += Eigen::VectorXd::Ones(system.getNbParticles()).asDiagonal();
}

void ComputeTemperatureFiniteDifferences::assembleRightHandSide(
    System& system) {
  rhs.resize(system.getNbParticles());
  std::transform(
      system.begin(), system.end(), rhs.begin(), [this](auto&& particle) {
        auto& mp = static_cast<MaterialPoint&>(particle);
        return dt / mp.getMass() * mp.getHeatSource() + mp.getTemperature();
      });
}
