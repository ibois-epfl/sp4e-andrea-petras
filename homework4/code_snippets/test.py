#!/bin/env python3

import pyexample
help(pyexample)

help(pyexample.add)
print(pyexample.add(1, 2))

help(pyexample.add_withparams)
print(pyexample.add_withparams(j=2, i=1))

help(pyexample.add_withdefaults)
print(pyexample.add_withdefaults())

print(pyexample.yopla)
print(pyexample.global_variable)
pyexample.global_variable = 1
print(pyexample.global_variable)
pyexample.print_var()
# conclusion ?
print(pyexample.global_variable_rw)
pyexample.global_variable_rw.fset(2)
# this do not work !!!
# pyexample.global_variable_rw = 2
pyexample.print_var()

help(pyexample.Animal)
print(pyexample.Animal)
a = pyexample.Animal('kitty')
b = pyexample.Animal()
a.python_extension()
print(a)
print(b)
a.scream()
print(a.name)
a.name = "new"
print(a.name)
print(a.name_property)

a.new_member = 'toto'
print(dir(a))
print(a.__dict__)

dog = pyexample.Dog('poppy')
dog.scream()
help(dog.overloadedFoo)

# automatic upcasting to true type (overhead)
d = pyexample.makeAnimalUnique()
print(type(d))
d.scream()

print(pyexample.ParticleType)
print(pyexample.ParticleType.__members__)


# Python and C++ use fundamentally different ways of managing the
# memory and lifetime of objects managed by them. This can lead to
# issues when creating bindings for functions that return a
# non-trivial type. Just by looking at the type information, it is not
# clear whether Python should take charge of the returned value and
# eventually free its resources, or if this is handled on the C++
# side. For this reason, pybind11 provides a several return value
# policy annotations that can be passed to the module::def() and
# class_::def() functions. The default policy is
# return_value_policy::automatic.

# segfault because del on python object calls delete on c++ pointer
print("segfault")
a = pyexample.get_animal()
print(a)
del a
a = pyexample.get_animal()
print(a)

# solution: copy
a = pyexample.get_animal_copy()
print(a)
a.name = "test"
del a
a = pyexample.get_animal_copy()
print(a)

# solution: by reference (no ownership)
# memory management made by C++ only
a = pyexample.get_animal_reference()
print(a)
a.name = "test"
del a
a = pyexample.get_animal_reference()
print(a)

# Code with invalid return value policies might access uninitialized
# memory or free data structures multiple times, which can lead to
# hard-to-debug non-determinism and segmentation faults, hence it is
# worth spending the time to understand all the different options in
# the table of return value policy.

# As an alternative to elaborate call policies and lifetime management
# logic, consider using smart pointers (see the section on Custom
# smart pointers for details). Smart pointers can tell whether an
# object is still referenced from C++ or Python, which generally
# eliminates the kinds of inconsistencies that can lead to crashes or
# undefined behavior. For functions returning smart pointers, it is
# not necessary to specify a return value policy.

a = pyexample.get_shared_ptr()
a.name = "test"
print(a)

pyexample.register_animal_shared(a)

pyexample.apply(lambda x: print(x*2))

# https://pybind11.readthedocs.io/en/stable/advanced/exceptions.html
# automatic management of standard exceptions

try:
    pyexample._raise()
except Exception as e:
    print(e)

# https://pybind11.readthedocs.io/en/stable/advanced/cast/index.html#
