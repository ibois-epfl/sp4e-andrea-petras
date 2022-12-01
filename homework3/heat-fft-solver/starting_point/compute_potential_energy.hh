#ifndef __COMPUTE_POTENTIAL_ENERGY__HH__
#define __COMPUTE_POTENTIAL_ENERGY__HH__

/* -------------------------------------------------------------------------- */
#include "compute_energy.hh"
#include "compute_interaction.hh"
/* -------------------------------------------------------------------------- */

//! Compute potential energy of system
class ComputePotentialEnergy : public ComputeEnergy {

  /* ------------------------------------------------------------------------ */
  /* Constructors/Destructors                                                 */
  /* ------------------------------------------------------------------------ */

public:
  ComputePotentialEnergy(ComputeInteraction& cForces);

  /* ------------------------------------------------------------------------ */
  /* Methods                                                                  */
  /* ------------------------------------------------------------------------ */

public:
  void compute(System& system) override;

  /* ------------------------------------------------------------------------ */
  /* Members                                                                  */
  /* ------------------------------------------------------------------------ */

protected:
  ComputeInteraction& cForces;
};

/* -------------------------------------------------------------------------- */
#endif  //__COMPUTE_POTENTIAL_ENERGY__HH__
