#ifndef __COMPUTE_BOUNDARY__HH__
#define __COMPUTE_BOUNDARY__HH__

/* -------------------------------------------------------------------------- */
#include "compute.hh"
/* -------------------------------------------------------------------------- */

//! Compute interaction with simulation box
class ComputeBoundary : public Compute {
  // Constructors/Destructors
public:
  ComputeBoundary(const Vector& xmin, const Vector& xmax);

  // Methods
public:
  void compute(System& system) override;

  // Members
protected:
  Vector xmin, xmax;
};

/* -------------------------------------------------------------------------- */
#endif  //__COMPUTE_BOUNDARY__HH__
