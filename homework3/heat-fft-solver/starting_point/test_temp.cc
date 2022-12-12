#include "compute_temperature.hh"
#include "material_points_factory.hh"
#include "material_point.hh"
#include "matrix.hh"
#include "my_types.hh"
#include <gtest/gtest.h>


/*****************************************************************/
class TempTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
    MaterialPointsFactory::getInstance();

    // initialize the material mpoints
    for (uint i = 0; i < Nmpoints; i++)
    {
      for (uint j = 0; j < Nmpoints; j++)
      {
        // implement linear distribution of mpoints
        std::shared_ptr<MaterialPoint> mp = std::make_shared<MaterialPoint>();
        Real x = LdomSize * ((i * LdomSize / Nmpoints) - 0.5);
        Real y = LdomSize * ((j * LdomSize / Nmpoints) - 0.5);
        mp->getPosition()[0] = x;
        mp->getPosition()[1] = y;

        mpoints.emplace_back(mp);
      }
    }

    // set the temperature properties
    ctemp = std::make_unique<ComputeTemperature>();
    ctemp->setDomainSize(LdomSize);
    ctemp->setHeatConductivity(1.0);
    ctemp->setHeatCapacity(1.0);
    ctemp->setDeltaT(0.1);
    ctemp->setMassDensity(1.0);
  }

protected:
    System sys;
    uint Nmpoints = 15*15;
    Real LdomSize = 1.0;
    std::vector<std::shared_ptr<MaterialPoint>> mpoints;
    std::unique_ptr<ComputeTemperature> ctemp;
};

/*****************************************************************/
TEST_F(TempTest, constant)
{
    // set the temperature properties
    Real T0 = 25.0;
    uint nSteps = 100;

    // feed particles to the system
    for (auto& mp : mpoints)
    {
        mp->setTemperature(T0);
        mp->setHeatRate(0.0);
        this->sys.addParticle(mp);
    }

    // temp should be constant
    for (uint i = 0; i < nSteps; i++)
    {
        this->ctemp->compute(sys);
        for (auto& mp : mpoints)
        {
            ASSERT_NEAR(mp->getTemperature(), T0, 1e-10);
        }
    }
}

/*****************************************************************/
TEST_F(TempTest, volumetric)
{
    // set the temperature properties
    uint nSteps = 100;

    // feed particles to the system
    for (auto& mp : mpoints)
    {
        // implement sinusoidal distribution of temperature
        Real x = mp->getPosition()[0];
        mp->setTemperature(sin(2 * M_PI * x / LdomSize));  ///< ref (1) consigne
        mp->setHeatRate(((2 * M_PI) / LdomSize) * sin((2 * M_PI * x) / LdomSize));  ///< ref (2) consigne
        this->sys.addParticle(mp);
    }

    // heat flux
    for (uint i = 0; i < nSteps; i++)
    {
        this->ctemp->compute(sys);
        for (auto& mp : mpoints)
        {
            Real x = mp->getPosition()[0];
            Real T = mp->getTemperature();
            ASSERT_NEAR(T, sin(2 * M_PI * x / LdomSize), 1e-10);
        }
    }
}