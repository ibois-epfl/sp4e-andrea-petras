#include <pybind11/pybind11.h>

namespace py = pybind11;

#include "compute_temperature.hh"
#include "csv_writer.hh"
#include "particles_factory_interface.hh"
#include "material_points_factory.hh"
#include "ping_pong_balls_factory.hh"
#include "planets_factory.hh"

#include "system_evolution.hh"
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

  // main objects
  py::class_<ParticlesFactoryInterface>(
      m, "ParticlesFactoryInterface",
      py::dynamic_attr()
      )
      .def("getInstance", &ParticlesFactoryInterface::getInstance, py::return_value_policy::reference);

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


  // compute objects/methods
  py::class_<SystemEvolution>(
      m, "SystemEvolution",
      py::dynamic_attr()
      )
      .def("addCompute", &SystemEvolution::addCompute, py::arg("compute"));

  py::class_<Compute, std::shared_ptr<Compute>>(m, "Compute");

  py::class_<ComputeTemperature, Compute, std::shared_ptr<ComputeTemperature>>(
      m, "ComputeTemperature",
      py::dynamic_attr()
      )
      .def(py::init<>())
      /* here we could have modified the .hh and add setters (i.e. setConductivity()):
      *     def_property("conductivity", &ComputeTemperature::getConductivity, &ComputeTemperature::setConductivity)
      *  but we can also use the def_property() method to set the private variables.
      */
      .def_property("conductivity", &ComputeTemperature::getConductivity, 
          [](ComputeTemperature& self, Real value) { self.getConductivity() = value; })
      .def_property("capacity", &ComputeTemperature::getCapacity, 
          [](ComputeTemperature& self, Real value) { self.getCapacity() = value; })
      .def_property("density", &ComputeTemperature::getDensity, 
          [](ComputeTemperature& self, Real value) { self.getDensity() = value; })
      .def_property("L", &ComputeTemperature::getL, 
          [](ComputeTemperature& self, Real value) { self.getL() = value; })
      .def_property("deltat", &ComputeTemperature::getDeltat, 
          [](ComputeTemperature& self, Real value) { self.getDeltat() = value; });
  
  py::class_<ComputeGravity, Compute, std::shared_ptr<ComputeGravity>>(
      m, "ComputeGravity",
      py::dynamic_attr()
      )
      .def(py::init<>())
      .def("setG", &ComputeGravity::setG);

  py::class_<ComputeVerletIntegration, Compute, std::shared_ptr<ComputeVerletIntegration>>(
      m, "ComputeVerletIntegration",
      py::dynamic_attr()
      )
      .def(py::init<Real>())
      .def("addInteraction", &ComputeVerletIntegration::addInteraction);


}
