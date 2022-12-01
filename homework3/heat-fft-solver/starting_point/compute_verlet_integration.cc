#include "compute_verlet_integration.hh"

ComputeVerletIntegration::ComputeVerletIntegration(Real dt) : dt(dt) {}

/* -------------------------------------------------------------------------- */

void ComputeVerletIntegration::setDeltaT(Real dt) { this->dt = dt; }

/* -------------------------------------------------------------------------- */

void ComputeVerletIntegration::compute(System& system) {
  UInt size = system.getNbParticles();

  for (auto& par : system) {
    par.getVelocity() += .5 * dt * par.getForce() / par.getMass();
    par.getPosition() += dt * par.getVelocity();
  }

  auto& sun = system.getParticle(0);
  sun.getPosition() = 0;

  for (auto& par : system)
    par.getForce() = 0;

  for (auto& interaction : interactions)
    interaction->compute(system);

  for (auto& par : system) {
    par.getVelocity() += .5 * dt * par.getForce() / par.getMass();
  }
}

/* -------------------------------------------------------------------------- */

void ComputeVerletIntegration::addInteraction(
    std::shared_ptr<ComputeInteraction> interaction) {
  interactions.push_back(interaction);
}
