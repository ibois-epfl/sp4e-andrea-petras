#ifndef __PLANET__HH__
#define __PLANET__HH__

/* -------------------------------------------------------------------------- */
#include "particle.hh"
/* -------------------------------------------------------------------------- */
#include <iostream>
/* -------------------------------------------------------------------------- */

//! Class for planet
class Planet : public Particle {
  // Methods
public:
  //! Get name
  std::string& getName() { return name; }

  // Inherited methods
public:
  void initself(std::istream& stream) override;
  void printself(std::ostream& stream) const override;

private:
  std::string name;
};

/* -------------------------------------------------------------------------- */
#endif  //__PLANET__HH__
