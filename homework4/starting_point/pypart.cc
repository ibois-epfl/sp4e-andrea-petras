#include <pybind11/pybind11.h>

namespace py = pybind11;

#include "compute_temperature.hh"
#include "csv_writer.hh"
#include "particles_factory_interface.hh"
#include "material_points_factory.hh"
#include "ping_pong_balls_factory.hh"
#include "planets_factory.hh"

#include "compute.hh"
#include "compute_temperature.hh"
#include "compute_gravity.hh"
#include "compute_verlet_integration.hh"

/*
from pypart import MaterialPointsFactory, ParticlesFactoryInterface
from pypart import PingPongBallsFactory, PlanetsFactory
from pypart import CsvWriter
from pypart import ComputeTemperature
from pypart import ComputeGravity
from pypart import ComputeVerletIntegration
*/


PYBIND11_MODULE(pypart, m) {

  m.doc() = "pybind of the Particles project";

  // bind the routines here
  py::class_<ParticlesFactoryInterface>(
      m, "ParticlesFactoryInterface",
      py::dynamic_attr()
      )
      .def("getInstance", &ParticlesFactoryInterface::getInstance, py::return_value_policy::reference)

  py::class_<MaterialPointsFactory, ParticlesFactoryInterface>(
      m, "MaterialPointsFactory",
      py::dynamic_attr()
      )
      .def("getInstance", &MaterialPointsFactory::getInstance, py::return_value_policy::reference);

  py::class_<PingPongBallsFactory, ParticlesFactoryInterface>(
      m, "PingPongBallsFactory",
      py::dynamic_attr()
      )
      .def("getInstance", &PingPongBallsFactory::getInstance, py::return_value_policy::reference);
  
  py::class_<PlanetsFactory, ParticlesFactoryInterface>(
      m, "PlanetsFactory",
      py::dynamic_attr()
      )
      .def("getInstance", &PlanetsFactory::getInstance, py::return_value_policy::reference);


  // py::class_<ComputeTemperature, Compute, std::shared_ptr<ComputeTemperature>>(
  //     m, "ComputeTemperature",
  //     py::dynamic_attr()
  //     )
  //     .def(py::init<>());

}
