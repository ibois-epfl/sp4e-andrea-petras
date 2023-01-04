#include <pybind11/pybind11.h>

namespace py = pybind11;

#include "compute_temperature.hh"
#include "csv_writer.hh"
#include "particles_factory_interface.hh"
#include "material_points_factory.hh"
#include "ping_pong_balls_factory.hh"
#include "planets_factory.hh"

#include "system.hh"
#include "system_evolution.hh"
#include "compute.hh"
#include "compute_temperature.hh"
#include "compute_gravity.hh"
#include "compute_verlet_integration.hh"

#include "csv_writer.hh"


PYBIND11_MODULE(pypart, m) {

  m.doc() = "pybind of the Particles project";

  /* -------------------------------------------------------------------------- */
  // system
  /* -------------------------------------------------------------------------- */

  py::class_<System>(
      m, "System")
      .def(py::init());


  /* -------------------------------------------------------------------------- */
  // main objects + simulation methods
  /* -------------------------------------------------------------------------- */

  py::class_<ParticlesFactoryInterface>(
      m, "ParticlesFactoryInterface"
      )
      .def_static("getInstance", &ParticlesFactoryInterface::getInstance, py::return_value_policy::reference)
      .def("createSimulation", [](ParticlesFactoryInterface& self, const std::string& fname, Real timestep)
          -> SystemEvolution& {return self.createSimulation(fname, timestep);},
          py::arg("fname"), py::arg("timestep"), py::return_value_policy::reference)
      .def("createSimulation", py::overload_cast<const std::string&, Real, py::function>(&ParticlesFactoryInterface::createSimulation<py::function>),
          py::arg("fname"), py::arg("timestep"), py::arg("create_computes"), py::return_value_policy::reference)
      .def_property_readonly("system_evolution", &ParticlesFactoryInterface::getSystemEvolution, py::return_value_policy::reference);

  py::class_<MaterialPointsFactory, ParticlesFactoryInterface>(
      m, "MaterialPointsFactory"
      )
      .def_static("getInstance", &MaterialPointsFactory::getInstance, py::return_value_policy::reference);

  py::class_<PingPongBallsFactory, ParticlesFactoryInterface>(
      m, "PingPongBallsFactory"
      )
      .def_static("getInstance", &PingPongBallsFactory::getInstance, py::return_value_policy::reference);
  
  py::class_<PlanetsFactory, ParticlesFactoryInterface>(
      m, "PlanetsFactory"
      )
      .def_static("getInstance", &PlanetsFactory::getInstance, py::return_value_policy::reference);


  /* -------------------------------------------------------------------------- */
  // compute objects/methods
  /* -------------------------------------------------------------------------- */

  py::class_<SystemEvolution>(
      m, "SystemEvolution"
      )
      .def("addCompute", &SystemEvolution::addCompute, py::arg("compute"))
      .def("getSystem", &SystemEvolution::getSystem);
      // .def_property_readonly("getSystem", &SystemEvolution::getSystem, py::return_value_policy::reference);

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
  
    py::class_<ComputeInteraction, Compute, std::shared_ptr<ComputeInteraction>>(m, "ComputeInteraction");
  
  py::class_<ComputeGravity, ComputeInteraction, std::shared_ptr<ComputeGravity>>(
      m, "ComputeGravity"
      )
      .def(py::init<>())
      .def("setG", &ComputeGravity::setG, py::arg("G"));

  py::class_<ComputeVerletIntegration, Compute, std::shared_ptr<ComputeVerletIntegration>>(
      m, "ComputeVerletIntegration"
      )
      .def(py::init<Real>())
      .def("addInteraction", &ComputeVerletIntegration::addInteraction);


  /* -------------------------------------------------------------------------- */
  // csv writer
  /* -------------------------------------------------------------------------- */

  py::class_<CsvWriter>(
      m, "CsvWriter"
      )
      .def(py::init<const std::string&>())
      .def("write", &CsvWriter::write);

}
