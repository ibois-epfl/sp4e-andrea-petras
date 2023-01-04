#include <functional>
#include <iostream>
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(pyexample, m) {
  m.doc() = "pybind pyexample plugin"; // optional docstring

  m.def("add",                            // name in python
        &add,                             // function to wrap
        "A function adding two arguments" // documentation help text
  );
  m.def("add_withparams", &add, "A function adding two named arguments",
        py::arg("i"), // naming first argument
        py::arg("j")  // naming second argument
  );

  m.def("add_withdefaults", &add, "A function adding two numbers with defaults",
        py::arg("i") = 1, // with default argument
        py::arg("j") = 2  // with default argument
  );

  // list of possible casts
  // https://pybind11.readthedocs.io/en/master/advanced/cast/index.html

  m.attr("yopla") = py::cast(yopla); // declaring a variable in module

  // Question, where are stored the C++ and python variables ?
  m.attr("global_variable") = py::cast(global_variable);
  m.def("print_var", []() { py::print(global_variable); },
        "test_memory_function"); // declaring a print function

  // setting a property
  // import the builtins and get the "property" python class
  auto property = py::module::import("builtins").attr("property");
  // py::print(property); // print object in the python style

  // make a property to have setter/getter for the global variable
  m.attr("global_variable_rw") =
      property(py::cpp_function([&]() { return global_variable; }),
               py::cpp_function([&](int &a) { global_variable = a; }));

  // wrap the class
  py::class_<Animal>(
      m, "Animal",
      py::dynamic_attr() // to allow new members to be created dynamically
      )
      .def(py::init<const std::string &>(), // constructor
           py::arg("name") = "puppy")       // with a default
      .def("scream", &Animal::scream)       // scream method
      .def("python_extension",              // extension method with a lambda
           [](Animal &a) { std::cout << a.name << std::endl; })
      .def("__repr__", // method to allow being printed
           [](const Animal &a) { return "<Animal: " + a.name + ">"; })
      .def_readwrite(
          "name", &Animal::name) // give read write access (property) to member
      .def_property(
          "name_property", &Animal::getName,
          &Animal::setName); // give read write access through acessors

  py::class_<Dog, Animal>(m, "Dog")
      .def(py::init<const std::string &>() // constructor

           )
      .def("hasNiche", &Dog::hasNiche) // method only in Dog;
      .def("overloadedFoo",
           py::overload_cast<int>(&Dog::overloadedFoo)) // overloading with int
      .def("overloadedFoo",
           py::overload_cast<const std::string>(
               &Dog::overloadedFoo, py::const_)); // overloading with const

  py::enum_<ParticleType>(m, "ParticleType")
      .value("atom", atom)
      .value("planet", planet)
      .value("pingpongball", pingpongball)
      .value("material", material)
      .export_values();

  m.def("makeAnimalUnique", &makeAnimalUnique);
  m.def("get_animal", &get_animal);
  m.def("get_animal_copy", &get_animal, py::return_value_policy::copy);
  m.def("get_animal_reference", &get_animal,
        py::return_value_policy::reference);

  py::class_<AnimalShared, std::shared_ptr<AnimalShared>>(m, "AnimalShared")
      .def_readwrite("name", &AnimalShared::name);

  m.def("get_shared_ptr", &get_shared_ptr);

  m.def("register_animal_shared", &register_animal_shared);

  m.def("apply", &apply<py::function>);

  m.def("_raise", &_raise);
}
