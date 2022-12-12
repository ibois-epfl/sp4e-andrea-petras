#ifndef __MATERIAL_POINT__HH__
#define __MATERIAL_POINT__HH__

/* -------------------------------------------------------------------------- */
#include "particle.hh"

//! Class for MaterialPoint
class MaterialPoint : public Particle {
  /* ------------------------------------------------------------------------ */
  /* Methods                                                                  */
  /* ------------------------------------------------------------------------ */

public:

  void printself(std::ostream& stream) const override;
  void initself(std::istream& sstr) override;

  Real & getTemperature(){return temperature;};
  Real & getHeatRate(){return heat_rate;};

  void setTemperature(Real _temperature){temperature = _temperature;};
  void setHeatRate(Real _heat_rate){heat_rate = _heat_rate;};
  
private:
  Real temperature;
  Real heat_rate;
};

/* -------------------------------------------------------------------------- */
#endif  //__MATERIAL_POINT__HH__
