# Homework4

# To consume the code
> Be sure to clone the submodules with the repository.
```bash
cd homework4/starting_point
cmake -S . -B build && cmake --build build && python build/main.py 365 1 "init.csv" "planet" 1
```

## First part - Pybind: Python bindings for Particles Code
### Exercise 1: Factory interface
**1.2 In class ParticlesFactory, createSimulation function has been overloaded to take functor as one
of its argument. Comment on what this function is doing? **
The overloading allows to specify extra info for which type of compute class and values are used in the creation of the evolution system. The basic function presents already a call of default instance of compute objects.

we followed the [pybind11 docu for overloading](https://pybind11.readthedocs.io/en/stable/classes.html#overloaded-methods) and we tried to implement this overload wrap for the `createSimulation()`:
```cpp
.def("createSimulation", py::overload_cast<const std::string&, Real>(&ParticlesFactoryInterface::createSimulation),
          py::arg("fname"), py::arg("timestep"), py::return_value_policy::reference)
.def("createSimulation", py::overload_cast<const std::string&, Real, py::function>(&ParticlesFactoryInterface::createSimulation<py::function>),
          py::arg("fname"), py::arg("timestep"), py::arg("create_computes"), py::return_value_policy::reference);
```
But we recived the error that it was an `unspecified overload the first one`, finally we decided to declare it as a simple function against the pybind11 documentation. *Why this did not work?*

### Exercise 2: Compute
**2.2 How will you ensure that references to Compute objects type are correctly managed in the python
bindings?**
The memory for these object's bindings is done via `shared pointers` this ensures that once both the C++ and Python memory management counters reach 0, the memory garbage collector takes care of it. As a general rule, this is how every object with no particular instantiation rules should be wrapped.

---
## Second part: Particle trajectory optimization
### Exercise 5: Compute the error of the simulation
To run the code:
```bash
cd homework4/starting_point
python compute_error_simulation.py "mercury" "trajectories" "build/dumps"
```

---
### Exercise 6: Launching the particle code from python by generating the input
To run the code:
```bash
cd homework4/starting_point
python generate_input_launcher.py 2 "mercury" "init.csv" "dumps" "build/dumps" "outVelocity.csv"
```
with args as (in order):
`scale` : the scaling factor
`planet_name` : the name of the planet to analyse
`input_filename` : the starting input filename to modify the velocity
`directory` : the generated dumps from this script
`directory_dir` : the previously generated dumps from the vanilla launcher
`output_filename` : the single output with modified data for veloctiy

* Generated results can be found in the directory: `homework/starting_point/dumps`.

---
### Exercice 7: Optimization
We did not menage to terminate the part 7 for the optimization in time. The optimization code is present but not working.