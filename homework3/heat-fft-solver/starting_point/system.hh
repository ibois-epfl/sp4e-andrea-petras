#ifndef __SYSTEM__HH__
#define __SYSTEM__HH__

/* -------------------------------------------------------------------------- */
#include "my_types.hh"
#include "particle.hh"
#include <memory>
#include <vector>
/* -------------------------------------------------------------------------- */

//! Container for particles
class System {

public:
  virtual ~System() = default;

  // List of particle pointers
  using ParticleList = std::vector<std::shared_ptr<Particle>>;

  //! Remove particle from vector
  void removeParticle(UInt particle){};
  //! Get particle for specific id
  Particle& getParticle(UInt i);
  //! Add a particle to the system
  void addParticle(const std::shared_ptr<Particle>& new_particle);
  //! Get number of particles
  UInt getNbParticles();

  //! Iterator class to erase the unique pointer on Particle
  struct iterator : ParticleList::iterator {
    iterator(const ParticleList::iterator& it) : ParticleList::iterator(it) {}

    //! Access the underlying particle
    Particle& operator*() { return *ParticleList::iterator::operator*(); }
  };

  // Iterators
public:
  auto begin() { return iterator(list_particles.begin()); }
  auto end() { return iterator(list_particles.end()); }

protected:
  ParticleList list_particles;
};

/* -------------------------------------------------------------------------- */

#endif  //__SYSTEM__HH__
