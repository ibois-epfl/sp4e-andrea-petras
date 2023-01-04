#include "system.hh"

Particle& System::getParticle(UInt i) { return *list_particles[i]; }

/* -------------------------------------------------------------------------- */

void System::addParticle(const std::shared_ptr<Particle>& new_particle) {
  list_particles.push_back(new_particle);
}

/* -------------------------------------------------------------------------- */

UInt System::getNbParticles() { return list_particles.size(); }
