#include "compute_gravity.hh"
#include "compute_verlet_integration.hh"
#include "csv_reader.hh"
#include "csv_writer.hh"
#include "my_types.hh"
#include "ping_pong_balls_factory.hh"
#include "material_points_factory.hh"
#include "planets_factory.hh"
#include "system.hh"
/* -------------------------------------------------------------------------- */
#include <cstdlib>
#include <iostream>
#include <sstream>
/* -------------------------------------------------------------------------- */

int main(int argc, char** argv) {
  if (argc != 6) {
    std::cout << "Usage: " << argv[0]
              << " nsteps dump_freq input.csv particle_type timestep"
              << std::endl;
    std::cout << "\tparticle type can be: planet, ping_pong, material_point" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  // the number of steps to perform
  Real nsteps;
  std::stringstream(argv[1]) >> nsteps;
  // freq to dump
  int freq;
  std::stringstream(argv[2]) >> freq;
  // init file
  std::string filename = argv[3];
  // particle type
  std::string type = argv[4];
  // timestep
  Real timestep;
  std::stringstream(argv[5]) >> timestep;

  if (type == "planet")
    PlanetsFactory::getInstance();
  else if (type == "ping_pong")
    PingPongBallsFactory::getInstance();
  else if (type == "material_point")
    MaterialPointsFactory::getInstance();  
  else {
    std::cout << "Unknown particle type: " << type << std::endl;
    std::exit(EXIT_FAILURE);
  }

  ParticlesFactoryInterface& factory = ParticlesFactoryInterface::getInstance();

  SystemEvolution& evol = factory.createSimulation(filename, timestep);

  evol.setNSteps(nsteps);
  evol.setDumpFreq(freq);

  evol.evolve();

  return EXIT_SUCCESS;
}
