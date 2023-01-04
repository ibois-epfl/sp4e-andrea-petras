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

  Real& getTemperature() { return temperature; };
  Real& getTemperatureRate() { return temperature_rate; };
  Real& getHeatSource() { return heat_source; };

private:
  Real temperature;
  Real temperature_rate;
  Real heat_source;
};

/* -------------------------------------------------------------------------- */
#endif  //__MATERIAL_POINT__HH__
