#include "compute_gravity.hh"
#include <cmath>
/* -------------------------------------------------------------------------- */
void ComputeGravity::setG(Real G) { this->G = G; }
/* -------------------------------------------------------------------------- */

void ComputeGravity::compute(System& system) {
  // define a lambda function for newtonian gravity
  auto newton_gravity = [this](Particle& par1, Particle& par2) {
    // compute the distance vector and the square of distance
    auto v_r = par2.getPosition() - par1.getPosition();
    auto r2 = v_r.squaredNorm();

    if (r2 == 0.)
      return;

    // compute the distance
    auto r = sqrt(r2);
    v_r *= 1 / r;

    // compute the pair force
    auto force = par1.getMass() * par2.getMass() * G / r2 * v_r;

    // add up the force for both concerned particles
    par2.getForce() -= force;
    par1.getForce() += force;
  };

  // apply newtonian gravity on all pairs of particles
  applyOnPairs(newton_gravity, system);
}
