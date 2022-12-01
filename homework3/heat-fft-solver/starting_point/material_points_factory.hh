#ifndef __MATERIAL_POINTS_FACTORY__HH__
#define __MATERIAL_POINTS_FACTORY__HH__

/* -------------------------------------------------------------------------- */
#include "particles_factory_interface.hh"
#include "material_point.hh"
/* -------------------------------------------------------------------------- */

//! Factory for material points
class MaterialPointsFactory : public ParticlesFactoryInterface {
  /* ------------------------------------------------------------------------ */
  /* Constructors/Destructors                                                 */
  /* ------------------------------------------------------------------------ */
private:
  MaterialPointsFactory() = default;

  /* ------------------------------------------------------------------------ */
  /* Methods                                                                  */
  /* ------------------------------------------------------------------------ */
public:
  SystemEvolution& createSimulation(const std::string& fname,
				    Real timestep) override;

  std::unique_ptr<Particle> createParticle() override;

  static ParticlesFactoryInterface& getInstance();
};

/* -------------------------------------------------------------------------- */
#endif  //__MATERIAL_POINTS_FACTORY__HH__
