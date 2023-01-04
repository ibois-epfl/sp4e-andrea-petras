#include "ping_pong_ball.hh"

/* -------------------------------------------------------------------------- */
void PingPongBall::printself(std::ostream& stream) const {
  Particle::printself(stream);
  stream << " " << radius;
}

/* -------------------------------------------------------------------------- */

void PingPongBall::initself(std::istream& sstr) {
  Particle::initself(sstr);
  sstr >> radius;
}
