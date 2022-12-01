#include "particles_factory_interface.hh"
#include "planets_factory.hh"
/* -------------------------------------------------------------------------- */
ParticlesFactoryInterface& ParticlesFactoryInterface::getInstance() {
  return *factory;
}

/* -------------------------------------------------------------------------- */
ParticlesFactoryInterface* ParticlesFactoryInterface::factory = nullptr;
