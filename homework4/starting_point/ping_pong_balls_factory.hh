#ifndef __PING_PING_BALLS_FACTORY__HH__
#define __PING_PING_BALLS_FACTORY__HH__

/* -------------------------------------------------------------------------- */
#include "particles_factory_interface.hh"
#include "ping_pong_ball.hh"
/* -------------------------------------------------------------------------- */

//! Factory for ping-pong balls
class PingPongBallsFactory : public ParticlesFactoryInterface {
  /* ------------------------------------------------------------------------ */
  /* Constructors/Destructors                                                 */
  /* ------------------------------------------------------------------------ */
private:
  PingPongBallsFactory() = default;

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
#endif  //__PING_PING_BALLS_FACTORY__HH__
