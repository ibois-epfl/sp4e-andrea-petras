#include "compute_contact.hh"
#include "ping_pong_ball.hh"
#include <cmath>
/* -------------------------------------------------------------------------- */
void ComputeContact::setPenalty(Real penalty) { this->penalty = penalty; }
/* -------------------------------------------------------------------------- */
void ComputeContact::compute(System& system) {
  auto penalty_contact = [this](Particle& par1, Particle& par2) {
    auto& ppb1 = static_cast<PingPongBall&>(par1);
    auto& ppb2 = static_cast<PingPongBall&>(par2);

    Vector v_r = ppb2.getPosition() - ppb1.getPosition();
    auto r = v_r.norm();
    v_r.normalize();

    auto penetration = ppb1.getRadius() + ppb2.getRadius() - r;

    Vector force;

    if (penetration > 0) {
      force = v_r;
      force *= penalty * penetration;

      ppb1.getForce() -= force;
      ppb2.getForce() += force;
    }
  };

  applyOnPairs(penalty_contact, system);
}
