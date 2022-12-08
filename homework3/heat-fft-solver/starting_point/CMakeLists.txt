
cmake_minimum_required (VERSION 3.1)
project (Particles)

set(CMAKE_CXX_STANDARD 14)


################################################################
# Options
################################################################

option(FFTW_MODULE "Use FFTW module" OFF)


################################################################
# libpart
################################################################

add_library(part
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
  material_points_factory.cc 
  )

add_executable(particles main.cc)
target_link_libraries(particles gtest_main gtest pthread part)

if(EXISTS "${PROJECT_SOURCE_DIR}/googletest_local/CMakeLists.txt")
  add_subdirectory(googletest_local)
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

################################################################
# FFTW
################################################################

if(FFTW_MODULE)
    # add precompiled variable
    target_compile_definitions(particles PRIVATE __FFTW_MODULE_ACTIVE__=true)
    
    # add library files
    set(FFTW_LIBRARIES_PATH CACHE PATH "/usr/lib/")
    find_library(FFTW_LIBRARIES NAMES libfftw3 PATHS ${FFTW_LIBRARIES_PATH})
    message(STATUS "FFTW_LIBRARIES: ${FFTW_LIBRARIES}")
    target_link_libraries(particles ${FFTW_LIBRARIES})

    # add library headers
    set(FFTW_INCLUDES_PATH CACHE PATH "/usr/include/")
    find_path(FFTW_INCLUDES NAMES fftw3.h PATHS ${FFTW_INCLUDES_PATH})
    message(STATUS "FFTW_INCLUDES: ${FFTW_INCLUDES}")
    target_include_directories(particles PUBLIC ${FFTW_INCLUDES})
endif()

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
