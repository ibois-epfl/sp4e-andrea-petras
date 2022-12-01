#include "compute_boundary.hh"
/* -------------------------------------------------------------------------- */
ComputeBoundary::ComputeBoundary(const Vector& xmin, const Vector& xmax)
    : xmin(xmin), xmax(xmax) {
  Vector d = xmax - xmin;
  for (UInt i = 0; i < Vector::dim; ++i)
    if (d[i] < 0) {
      std::cout << "XMax and XMin do not form a domain range" << std::endl;
      std::exit(1);
    }
}
/* -------------------------------------------------------------------------- */

void ComputeBoundary::compute(System& system) {
  for (auto& par : system) {
    auto& x = par.getPosition();
    auto& v = par.getVelocity();

    Vector d1 = xmax - x, d2 = x - xmin;

    for (UInt i = 0; i < Vector::dim; ++i) {
      if (d1[i] < 0 or d2[i] < 0)
        v[i] *= -1;
    }
  }
}

/* -------------------------------------------------------------------------- */
