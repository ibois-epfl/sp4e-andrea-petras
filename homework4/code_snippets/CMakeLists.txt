cmake_minimum_required(VERSION 2.8.12)
project(example)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD 14)

find_package(pybind11 REQUIRED)  # or add_subdirectory(pybind11)

add_library(pyexample MODULE pyexample.cpp)
target_link_libraries(pyexample PRIVATE pybind11::module)
set_target_properties(pyexample PROPERTIES PREFIX "${PYTHON_MODULE_PREFIX}"
                                           SUFFIX "${PYTHON_MODULE_EXTENSION}")

file(
  COPY ${CMAKE_CURRENT_SOURCE_DIR}/test.py
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/
  )


