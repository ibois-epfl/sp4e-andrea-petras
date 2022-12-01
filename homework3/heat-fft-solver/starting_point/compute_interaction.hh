#ifndef __COMPUTE_INTERACTION__HH__
#define __COMPUTE_INTERACTION__HH__

/* -------------------------------------------------------------------------- */
#include "compute.hh"

//! Base class for interaction computation
class ComputeInteraction : public Compute {
public:
  //! Apply a functor on all particle pairs
  template <typename Functor>
  void applyOnPairs(Functor func, System& system);
};

/* -------------------------------------------------------------------------- */
/* Template implementation */
/* -------------------------------------------------------------------------- */
template <typename Functor>
void ComputeInteraction::applyOnPairs(Functor func, System &system) {
  UInt size = system.getNbParticles();

  for (UInt p1 = 0; p1 < size; ++p1) {
    Particle& par1 = system.getParticle(p1);
    for (UInt p2 = p1 + 1; p2 < size; ++p2) {
      Particle& par2 = system.getParticle(p2);
      func(par1, par2);
    }
  }
}

/* -------------------------------------------------------------------------- */
#endif  //__COMPUTE_INTERACTION__HH__
