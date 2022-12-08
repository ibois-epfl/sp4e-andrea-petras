#ifndef __COMPUTE_TEMPERATURE__HH__
#define __COMPUTE_TEMPERATURE__HH__

/* -------------------------------------------------------------------------- */
#include "compute.hh"

//! Compute contact interaction between ping-pong balls
class ComputeTemperature : public Compute {

  // Virtual implementation
public:
  //! Penalty contact implementation
  void compute(System& system) override;

public: __always_inline
    void setDomainSize(Real LdomSize) {m_DomSize = LdomSize;}  ///< Set domain size
    void setHeatConductivity(Real heatConductivity) {m_HeatConductivity = heatConductivity;}  ///< Set heat conductivity
    void setHeatCapacity(Real heatCapacity) {m_HeatCapacity = heatCapacity;};  ///< Set heat capacity
    void setDeltaT(Real timeStep) {m_Tstep = timeStep;};  ///< Set time step
    void setMassDensity(Real massDensity) {m_MassDensity = massDensity;}  ///< Set mass density

private:
    Real m_DomSize; ///< Domain size
    Real m_HeatConductivity; ///< Heat conductivity
    Real m_HeatCapacity; ///< Heat capacity
    Real m_Tstep; ///< Time step
    Real m_MassDensity; ///< Mass density
};

/* -------------------------------------------------------------------------- */
#endif  //__COMPUTE_TEMPERATURE__HH__
