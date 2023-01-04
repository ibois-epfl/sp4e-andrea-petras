#ifndef __PLANETS_FACTORY__HH__
#define __PLANETS_FACTORY__HH__

/* -------------------------------------------------------------------------- */
#include "particles_factory_interface.hh"
#include "planet.hh"
/* -------------------------------------------------------------------------- */

//! Factory for planet simulations
class PlanetsFactory : public ParticlesFactoryInterface {
  /* ------------------------------------------------------------------------ */
  /* Constructors/Destructors                                                 */
  /* ------------------------------------------------------------------------ */
private:
  PlanetsFactory() {
    createComputes = [&](Real timestep) {
      this->createDefaultComputes(timestep);
    };
  };

  /* ------------------------------------------------------------------------ */
  /* Methods                                                                  */
  /* ------------------------------------------------------------------------ */

public:
  SystemEvolution& createSimulation(const std::string& fname,
                                    Real timestep) override;

  void createDefaultComputes(Real timestep);

  std::unique_ptr<Particle> createParticle() override;

  static ParticlesFactoryInterface& getInstance();
};

/* -------------------------------------------------------------------------- */
#endif  //__PLANETS_FACTORY__HH__
