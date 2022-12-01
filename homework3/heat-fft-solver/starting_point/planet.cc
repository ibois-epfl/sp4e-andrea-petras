#include "planet.hh"

void Planet::initself(std::istream& stream) {
  Particle::initself(stream);
  stream >> name;
}

/* -------------------------------------------------------------------------- */

void Planet::printself(std::ostream& stream) const {
  Particle::printself(stream);
  stream << " " << name;
}
