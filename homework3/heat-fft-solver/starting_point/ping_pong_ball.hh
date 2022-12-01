#ifndef __PING_PONG_BALL__HH__
#define __PING_PONG_BALL__HH__

/* -------------------------------------------------------------------------- */
#include "particle.hh"

//! Class for ping-pong ball
class PingPongBall : public Particle {
  /* ------------------------------------------------------------------------ */
  /* Methods                                                                  */
  /* ------------------------------------------------------------------------ */

public:
  //! Get contact dissipation
  Real& getContactDissipation() { return contact_dissipation; }
  //! Get ball radius
  Real& getRadius() { return radius; }

  void printself(std::ostream& stream) const override;
  void initself(std::istream& sstr) override;

private:
  Real radius, contact_dissipation;
};

/* -------------------------------------------------------------------------- */
#endif  //__PING_PONG_BALL__HH__
