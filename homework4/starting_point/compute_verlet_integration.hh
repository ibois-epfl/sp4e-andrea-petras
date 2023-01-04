#ifndef __COMPUTE_VERLET_INTEGRATION__HH__
#define __COMPUTE_VERLET_INTEGRATION__HH__

/* -------------------------------------------------------------------------- */
#include "compute.hh"
#include "compute_interaction.hh"
/* -------------------------------------------------------------------------- */
#include <cmath>

//! Integrate equation of motion
class ComputeVerletIntegration : public Compute {
  using InteractionList = std::vector<std::shared_ptr<ComputeInteraction>>;

  // Constructors/Destructors
public:
  ComputeVerletIntegration(Real timestep);

  // Methods
public:
  //! Set time step
  void setDeltaT(Real dt);
  //! Evolve positions and velocities
  void compute(System& system) override;
  //! Add an interaction to the computation of forces
  void addInteraction(std::shared_ptr<ComputeInteraction> interaction);

private:
  Real dt;
  InteractionList interactions;
};

/* -------------------------------------------------------------------------- */
#endif  //__COMPUTE_VERLET_INTEGRATION__HH__
