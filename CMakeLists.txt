cmake_minimum_required(VERSION 3.10)
project(FEUP-AEDA-Proj1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# add_subdirectory(lib/googletest-master)

file(GLOB FEUP-AEDA-Proj1_FILES
  "include/*.h"
  "src/*.cpp"
  # "tests/*.cpp"
  # "lib/googletest-master/googletest/include/*"
  # "lib/googletest-master/googlemock/include/*"
  )

add_executable(FEUP-AEDA-Proj1 ${FEUP-AEDA-Proj1_FILES} main.cpp)
# target_link_libraries(FEUP-AEDA-Proj1 gtest gtest_main)

# Doxygen Build
# find_package(Doxygen)
# if(DOXYGEN_FOUND)
  # message("Doxygen installation found.")
  # set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs/output")
  # if(NOT EXISTS "${BUILD_DOC_DIR}")
    # file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
  # endif()

  # set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile")
  # set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
  # configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)

  # message("Doxygen build started")
  # add_custom_target(doc ALL
    # COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
    # WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    # COMMENT "Generating API documentation with Doxygen"
    # VERBATIM)

# else(DOXYGEN_FOUND)
  # message("Doxygen needs to be installed to generate the documentation.")
# endif(DOXYGEN_FOUND)
