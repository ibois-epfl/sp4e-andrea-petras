
cmake_minimum_required (VERSION 3.1)
project (Particles)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

################################################################
# FFTW
################################################################

find_package(FFTW)

################################################################
# libpart
################################################################

add_library(part SHARED
  compute_boundary.cc
  compute_verlet_integration.cc 
  particle.cc 
  planet.cc
  compute_gravity.cc 
  csv_reader.cc 
  particles_factory_interface.cc 
  planets_factory.cc 
  compute_contact.cc 
  compute_kinetic_energy.cc 
  csv_writer.cc 
  system.cc 
  compute_energy.cc 
  compute_potential_energy.cc 
  ping_pong_ball.cc
  material_point.cc 
  system_evolution.cc 
  ping_pong_balls_factory.cc 
  compute_interaction.cc
  compute_temperature.cc
  compute_temperature_finite_differences.cc
  material_points_factory.cc 
  )

if(EXISTS "${PROJECT_SOURCE_DIR}/eigen/CMakeLists.txt")
  include_directories(${PROJECT_SOURCE_DIR}/eigen)  
else()
  message("
*********************************************
eigen is missing. 
Did you forget `git submodule update --init`
*********************************************
")
  message(FATAL_ERROR "exit")
endif()

if(EXISTS "${PROJECT_SOURCE_DIR}/googletest/CMakeLists.txt")
  add_subdirectory(googletest)
  add_executable(test_kepler test_kepler.cc)
  add_executable(test_fft test_fft.cc)
  target_link_libraries(test_kepler part gtest_main gtest pthread )
  target_link_libraries(test_fft part gtest_main gtest pthread ${FFTW_LIBRARIES})
  add_custom_target(test ./test_kepler && ./test_fft DEPENDS part test_kepler test_fft)
else()
  message("
*********************************************
google tests is missing. 
Did you forget `git submodule update --init`
*********************************************
")
  message(FATAL_ERROR "exit")
endif()

include_directories(.)
target_link_libraries(part ${FFTW_LIBRARIES})
add_executable(particles main.cc)
target_link_libraries(particles gtest_main gtest pthread part)

################################################################
# Doxygen
################################################################

find_package(Doxygen)
if (DOXYGEN_FOUND)

  # to set other options, read: https://cmake.org/cmake/help/v3.9/module/FindDoxygen.html
  set(DOXYGEN_EXCLUDE_PATTERNS */googletest/*)

  doxygen_add_docs(
    doxygen
    ${PROJECT_SOURCE_DIR}
    COMMENT "Generate html pages"
    )
  add_custom_target(doc DEPENDS doxygen)
endif(DOXYGEN_FOUND)

################################################################
# Pybind
################################################################

option (USE_PYTHON "Use pybind library" OFF) 

if (USE_PYTHON)
add_subdirectory(pybind11)

add_library(pypart MODULE pypart.cc)
target_link_libraries(pypart PRIVATE pybind11::module part)
set_target_properties(pypart PROPERTIES
  PREFIX "${PYTHON_MODULE_PREFIX}"
  SUFFIX "${PYTHON_MODULE_EXTENSION}"
  )

file(
  COPY ${CMAKE_CURRENT_SOURCE_DIR}/main.py
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/
  )

endif(USE_PYTHON)
