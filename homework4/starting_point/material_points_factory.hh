#ifndef __MATERIAL_POINTS_FACTORY__HH__
#define __MATERIAL_POINTS_FACTORY__HH__

/* -------------------------------------------------------------------------- */
#include "material_point.hh"
#include "particles_factory_interface.hh"
/* -------------------------------------------------------------------------- */

//! Factory for material points
class MaterialPointsFactory : public ParticlesFactoryInterface {
  /* ------------------------------------------------------------------------ */
  /* Constructors/Destructors                                                 */
  /* ------------------------------------------------------------------------ */
private:
  MaterialPointsFactory() {
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
#endif  //__MATERIAL_POINTS_FACTORY__HH__
