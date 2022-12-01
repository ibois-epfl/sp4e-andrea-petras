#ifndef __COMPUTE__HH__
#define __COMPUTE__HH__

/* -------------------------------------------------------------------------- */
#include "system.hh"
/* -------------------------------------------------------------------------- */

//! Base class for all compute
class Compute {
public:
  //! Virtual destructor needed because we have subclasses
  virtual ~Compute() = default;

  /* ------------------------------------------------------------------------ */
  /* Methods                                                                  */
  /* ------------------------------------------------------------------------ */
public:
  //! Compute is pure virtual
  virtual void compute(System& system) = 0;
};

/* -------------------------------------------------------------------------- */
#endif  //__COMPUTE__HH__
