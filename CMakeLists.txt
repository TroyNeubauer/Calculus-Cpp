cmake_minimum_required(VERSION 3.1)

project(calculuscpp
  DESCRIPTION "A modern library for calculus, with respect to physics"
  LANGUAGES CXX
)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(src)

#
# Compile tools / tests / benchmarks
#
if(NOT(CALCULUSCPP_JUST_LIBRARY))
  add_subdirectory(tests)
  add_subdirectory(examples)
  add_subdirectory(bench)
else()
  message(STATUS "Building just the library, omitting all tests, tools and benchmarks.")
endif()

