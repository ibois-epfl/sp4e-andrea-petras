#ifndef COMPUTE_TEMPERATURE_FINITE_DIFFERENCES_HH
#define COMPUTE_TEMPERATURE_FINITE_DIFFERENCES_HH

#include "compute.hh"
#include <Eigen/SparseCore>
#include <Eigen/SparseLU>

class ComputeTemperatureFiniteDifferences : public Compute {
  using SparseMatrix = Eigen::SparseMatrix<Real, Eigen::ColMajor>;
  using Solver = Eigen::SparseLU<SparseMatrix>;

public:
  ComputeTemperatureFiniteDifferences(Real dt) : dt(dt) {}

  void compute(System& system) override;
  void assembleLinearOperator(System& system);
  void assembleRightHandSide(System& system);

protected:
  Real dt;
  Eigen::VectorXd rhs;
  SparseMatrix A;
  Solver solver;
};

#endif  // COMPUTE_TEMPERATURE_FINITE_DIFFERENCES_HH
