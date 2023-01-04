#ifndef __COMPUTE_CONTACT__HH__
#define __COMPUTE_CONTACT__HH__

/* -------------------------------------------------------------------------- */
#include "compute_interaction.hh"

//! Compute contact interaction between ping-pong balls
class ComputeContact : public ComputeInteraction {

  // Virtual implementation
public:
  //! Penalty contact implementation
  void compute(System& system) override;

  // Accessors
public:
  //! Set penalty
  void setPenalty(Real penalty);

  // Members
protected:
  Real penalty;
};

/* -------------------------------------------------------------------------- */
#endif  //__COMPUTE_CONTACT__HH__
