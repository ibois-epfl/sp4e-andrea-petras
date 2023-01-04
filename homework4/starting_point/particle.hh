#ifndef __PARTICLE__HH__
#define __PARTICLE__HH__

/* -------------------------------------------------------------------------- */
#include "vector.hh"
/* -------------------------------------------------------------------------- */

//! Particle base class
class Particle {
  /* ------------------------------------------------------------------------ */
  /* Constructors/Destructors                                                 */
  /* ------------------------------------------------------------------------ */
public:
  //! Default destructor (virtual because of virtual functions in this class)
  virtual ~Particle() = default;

  // Accessors
public:
  //! Get mass
  Real& getMass() { return mass; }
  //! Get position
  Vector& getPosition() { return position; }
  //! Get force
  Vector& getForce() { return force; }
  //! Get velocity
  Vector& getVelocity() { return velocity; }

  // I/O functions
public:
  /// function to print the content of the class
  virtual void printself(std::ostream& stream) const;

  /// function to initilize values from input files
  virtual void initself(std::istream& sstr);

  // Members
protected:
  Real mass;
  Vector position, force, velocity;
};

/* -------------------------------------------------------------------------- */
/* Inline functions */
/* -------------------------------------------------------------------------- */

inline std::istream& operator>>(std::istream& sstr, Particle& _this) {
  _this.initself(sstr);
  return sstr;
}

/* -------------------------------------------------------------------------- */
inline std::ostream& operator<<(std::ostream& sstr, Particle& _this) {
  _this.printself(sstr);
  return sstr;
}

/* -------------------------------------------------------------------------- */
#endif  //__PARTICLE__HH__
