#ifndef __COMPUTE_TEMPERATURE__HH__
#define __COMPUTE_TEMPERATURE__HH__

/* -------------------------------------------------------------------------- */
#include "compute.hh"

//! Compute heat equation evolution
class ComputeTemperature : public Compute {

public:
  //! temperature evolution implementation
  void compute(System& system) override;

  //! return the heat conductivity
  Real& getConductivity() { return conductivity; };
  //! return the heat capacity
  Real& getCapacity() { return capacity; };
  //! return the heat capacity
  Real& getDensity() { return density; };
  //! return the characteristic length of the square
  Real& getL() { return L; };
  //! return the characteristic length of the square
  Real& getDeltat() { return delta_t; };

  bool implicit = true;

private:
  Real conductivity;
  Real capacity;
  Real density;
  //! side length of the problem
  Real L;

  Real delta_t;
};

/* -------------------------------------------------------------------------- */
#endif  //__COMPUTE_TEMPERATURE__HH__
