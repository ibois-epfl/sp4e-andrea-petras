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
        Real x = LdomSize * ((i+0.5) / Nmpoints - 0.5);  ///< [-1,1] x [-1,1]
        Real y = LdomSize * ((j+0.5) / Nmpoints - 0.5);  ///< [-1,1] x [-1,1]
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
    Real LdomSize = 2.0;  ///< [-1,1] x [-1,1]
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

    // compute and test temp
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
TEST_F(TempTest, sinusoidal)
{
    // set the temperature properties
    uint nSteps = 20;

    // feed particles to the system
    for (auto& mp : mpoints)
    {
        // implement sinusoidal distribution of temperature
        Real x = mp->getPosition()[0];
        mp->setTemperature(sin(2 * M_PI * x / LdomSize));  ///< ref (1) consigne exo3
        mp->setHeatRate(pow(((2 * M_PI) / LdomSize), 2) * sin((2 * M_PI * x) / LdomSize));  ///< ref (2) consigne exo3
        this->sys.addParticle(mp);
    }

    // compute and test temp
    for (uint i = 0; i < nSteps; i++)
    {
        this->ctemp->compute(sys);

        for (auto& mp : mpoints)
        {
            Real x = mp->getPosition()[0];
            Real T = mp->getTemperature();
            Real gtT = sin(2 * M_PI * x / LdomSize);
            ASSERT_NEAR(T, gtT, 1e-10);
        }
    }
}

/*****************************************************************/
TEST_F(TempTest, volumetric)
{
    // set steps
    uint nSteps = 20;

    // feed particles to the system
    for (auto& mp : mpoints)
    {
        // implement volumetric distribution of temperature
        Real x = mp->getPosition()[0];
        Real y = mp->getPosition()[1];

        // Exo 4.3
        if (x == (1/2)) mp->setHeatRate(1.0);
        else if (x == (-1/2)) mp->setHeatRate(-1.0);
        else mp->setHeatRate(0.0);

        // Exo 4.4
        if (x <= -(1/2)) mp->setTemperature(-x-1.0);
        else if (x > -(1/2) && x <= (1/2)) mp->setTemperature(x);
        else if (x > (1/2)) mp->setTemperature(-x+1.0);

        this->sys.addParticle(mp);
    }

    // compute and test temp
    for (uint i = 0; i < nSteps; i++)
    {
        this->ctemp->compute(sys);

        for (auto& mp : mpoints)
        {
            Real x = mp->getPosition()[0];
            Real y = mp->getPosition()[1];
            Real T = mp->getTemperature();

            Real gtT = 0.0;

            if (x <= -(1/2)) gtT = -x-1.0;
            else if (x > -(1/2) && x <= (1/2)) gtT = x;
            else if (x > (1/2)) gtT = -x+1.0;

            ASSERT_NEAR(T, gtT, 1e-10);
        }
    }
}