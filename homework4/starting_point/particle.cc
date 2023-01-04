#include "particle.hh"

void Particle::printself(std::ostream& stream) const {
  stream << " " << position;
  stream << " " << velocity;
  stream << " " << force;
  stream << " " << mass;
}

/* -------------------------------------------------------------------------- */

void Particle::initself(std::istream& sstr) {
  sstr >> position;
  sstr >> velocity;
  sstr >> force;
  sstr >> mass;
}
