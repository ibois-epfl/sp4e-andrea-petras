#include "compute_gravity.hh"
#include "compute_verlet_integration.hh"
#include "csv_reader.hh"
#include "csv_writer.hh"
#include "planet.hh"
#include "planets_factory.hh"
#include "system.hh"
#include <gtest/gtest.h>

/*****************************************************************/
// Fixture class
class RandomPlanets : public ::testing::Test {
protected:
  void SetUp() override {
    PlanetsFactory::getInstance();
    std::vector<Planet> planets;
    n_planets = 10;
    for (UInt i = 0; i < n_planets; ++i) {
      Planet p;
      p.getPosition() = Vector::Ones();
      p.getForce() = Vector::Zero();
      p.getVelocity() = Vector::Zero();
      p.getMass() = 1.;
      planets.push_back(p);
    }

    for (auto& p : planets) {
      // std::cout << p << std::endl;
      system.addParticle(std::make_shared<Planet>(p));
    }
  }

  System system;
  UInt n_planets;
};

/*****************************************************************/
TEST_F(RandomPlanets, csv) {
  CsvWriter writer("tmp_file");
  writer.compute(system);

  CsvReader reader("tmp_file");
  System s_fromfile;
  reader.compute(s_fromfile);

  UInt read_n_planets = s_fromfile.getNbParticles();
  EXPECT_EQ(n_planets, s_fromfile.getNbParticles());

  for (UInt i = 0; i < n_planets; ++i) {
    auto& part1 = system.getParticle(i);
    auto& pos1 = part1.getPosition();
    auto& part2 = s_fromfile.getParticle(i);
    auto& pos2 = part2.getPosition();
    for (UInt j = 0; j < 3; ++j) {
      ASSERT_NEAR(pos1[j], pos2[j], std::abs(pos1[j]) * 1e-12);
    }
  }
}
/*****************************************************************/

// Fixture class
class TwoPlanets : public ::testing::Test {

protected:
  void SetUp() override {
    Planet p1, p2;
    p1.getMass() = 1.;
    p2.getMass() = 1.;
    p1.getPosition() = Vector::Zero();
    p2.getPosition() = Vector::Zero();
    p1.getVelocity() = Vector::Zero();
    p2.getVelocity() = Vector::Zero();
    p1.getForce() = Vector::Zero();
    p2.getForce() = Vector::Zero();
    system.addParticle(std::make_shared<Planet>(p1));
    system.addParticle(std::make_shared<Planet>(p2));
    n_planets = 2;

    gravity = std::make_shared<ComputeGravity>();
    verlet = std::make_shared<ComputeVerletIntegration>(1.);
    verlet->addInteraction(this->gravity);
  }

  System system;
  UInt n_planets;

  std::shared_ptr<ComputeGravity> gravity;
  std::shared_ptr<ComputeVerletIntegration> verlet;
};

/*****************************************************************/
TEST_F(TwoPlanets, gravity_force) {
  auto& p1 = system.getParticle(0);
  auto& p2 = system.getParticle(1);

  p2.getVelocity()[1] = 1.2;
  p2.getPosition()[0] = 1.;

  gravity->setG(1.);
  gravity->compute(system);

  ASSERT_NEAR(p1.getForce()[0], 1, 1e-15);
  ASSERT_NEAR(p2.getForce()[0], -1, 1e-15);
  ASSERT_NEAR(p1.getForce()[1], 0., 1e-15);
  ASSERT_NEAR(p2.getForce()[1], 0., 1e-15);
  ASSERT_NEAR(p1.getForce()[2], 0., 1e-15);
  ASSERT_NEAR(p2.getForce()[2], 0., 1e-15);
}

/*****************************************************************/
TEST_F(TwoPlanets, ellipsoid) {
  auto& p1 = system.getParticle(0);
  auto& p2 = system.getParticle(1);

  verlet->setDeltaT(5e-3);
  gravity->setG(1.);

  p1.getForce()[1] = 1e-4;

  p2.getPosition()[0] = 1.;
  p2.getForce()[1] = -1e-4;
  p2.getMass() = 1e-4;
  p2.getVelocity()[1] = 0.5;

  Real min_dist = std::numeric_limits<Real>::max();
  Real max_dist = -std::numeric_limits<Real>::max();

  for (UInt i = 0; i < 10000; ++i) {
    verlet->compute(system);
    auto dist = (p2.getPosition() - p1.getPosition()).squaredNorm();
    min_dist = std::min(min_dist, dist);
    max_dist = std::max(max_dist, dist);
  }
  Real excentricity = (max_dist - min_dist) / (max_dist + min_dist);
  // std::cout << "excentricity:" << excentricity << std::endl;
  ASSERT_LT(excentricity, 1.);
}

/*****************************************************************/
TEST_F(TwoPlanets, circular) {
  auto& p1 = system.getParticle(0);
  auto& p2 = system.getParticle(1);

  CsvWriter writer("tmp_file");
  writer.compute(system);

  verlet->setDeltaT(5e-3);
  // verlet->setDeltaT(1e-8);
  gravity->setG(1.);

  p1.getForce()[1] = 1e-4;

  p2.getPosition()[0] = 1.;
  p2.getForce()[1] = -1e-4;
  p2.getMass() = 1e-4;
  p2.getVelocity()[1] = 1.;

  for (UInt i = 0; i < 100000; ++i) {
    verlet->compute(system);
    auto dist = (p2.getPosition() - p1.getPosition()).squaredNorm();
    // ASSERT_NEAR(dist, 1., 1e-10);
    ASSERT_NEAR(dist, 1., 1e-1);
  }
}
