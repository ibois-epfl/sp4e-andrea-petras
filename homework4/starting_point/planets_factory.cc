#include "planets_factory.hh"
#include "compute_gravity.hh"
#include "compute_verlet_integration.hh"
#include "csv_reader.hh"
#include "csv_writer.hh"
#include "planet.hh"
#include <cmath>
/* -------------------------------------------------------------------------- */

std::unique_ptr<Particle> PlanetsFactory::createParticle() {

  return std::make_unique<Planet>();
}

/* -------------------------------------------------------------------------- */

void PlanetsFactory::createDefaultComputes(Real timestep) {

  auto gravity = std::make_shared<ComputeGravity>();
  auto verlet = std::make_shared<ComputeVerletIntegration>(timestep);

  verlet->addInteraction(gravity);
  this->system_evolution->addCompute(verlet);
}

/* -------------------------------------------------------------------------- */

SystemEvolution& PlanetsFactory::createSimulation(const std::string& fname,
                                                  Real timestep) {

  this->system_evolution =
      std::make_unique<SystemEvolution>(std::make_unique<System>());

  CsvReader reader(fname);
  reader.read(this->system_evolution->getSystem());

  this->createComputes(timestep);

  return *this->system_evolution;
}

/* -------------------------------------------------------------------------- */

ParticlesFactoryInterface& PlanetsFactory::getInstance() {

  if (not ParticlesFactoryInterface::factory)
    ParticlesFactoryInterface::factory = new PlanetsFactory;

  return *factory;
}
/* -------------------------------------------------------------------------- */
