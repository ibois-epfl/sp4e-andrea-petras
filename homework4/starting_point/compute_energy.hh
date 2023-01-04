#ifndef __COMPUTE_ENERGY__HH__
#define __COMPUTE_ENERGY__HH__

/* -------------------------------------------------------------------------- */
#include "compute.hh"

//! Base class for energy computation
class ComputeEnergy : public Compute {

  // Methods
public:
  Real getValue() { return value; }

protected:
  Real value;
};

/* -------------------------------------------------------------------------- */
#endif  //__COMPUTE_ENERGY__HH__
