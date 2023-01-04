#include "material_points_factory.hh"
#include "compute_temperature.hh"
#include "csv_reader.hh"
#include "csv_writer.hh"
#include "material_point.hh"
#include <cmath>
#include <iostream>
/* -------------------------------------------------------------------------- */

std::unique_ptr<Particle> MaterialPointsFactory::createParticle() {
  return std::make_unique<MaterialPoint>();
}

/* -------------------------------------------------------------------------- */

void MaterialPointsFactory::createDefaultComputes(Real timestep) {

  auto compute_temp = std::make_shared<ComputeTemperature>();
  compute_temp->getConductivity() = 1.;
  compute_temp->getL() = 2.;
  compute_temp->getCapacity() = 1.;
  compute_temp->getDensity() = 1.;
  compute_temp->getDeltat() = timestep;
  this->system_evolution->addCompute(compute_temp);
}

/* -------------------------------------------------------------------------- */

SystemEvolution&
MaterialPointsFactory::createSimulation(const std::string& fname,
                                        Real timestep) {

  this->system_evolution =
      std::make_unique<SystemEvolution>(std::make_unique<System>());

  CsvReader reader(fname);
  reader.read(this->system_evolution->getSystem());

  // check if it is a square number
  auto N = this->system_evolution->getSystem().getNbParticles();
  int side = std::sqrt(N);
  if (side * side != N)
    throw std::runtime_error("number of particles is not square");

  this->createComputes(timestep);
  return *system_evolution;
}

/* -------------------------------------------------------------------------- */

ParticlesFactoryInterface& MaterialPointsFactory::getInstance() {
  if (not ParticlesFactoryInterface::factory)
    ParticlesFactoryInterface::factory = new MaterialPointsFactory;

  return *factory;
}

/* -------------------------------------------------------------------------- */
