#ifndef __COMPUTE_KINETIC_ENERGY__HH__
#define __COMPUTE_KINETIC_ENERGY__HH__

/* -------------------------------------------------------------------------- */
#include "compute_energy.hh"

//! Compute kinetic energy of system
class ComputeKineticEnergy : public ComputeEnergy {
public:
  void compute(System& system) override;
};

/* -------------------------------------------------------------------------- */
#endif  //__COMPUTE_KINETIC_ENERGY__HH__
