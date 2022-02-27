cmake_minimum_required(VERSION 3.8...3.22.2)


# Let's build shared libs (*.so)
option(BUILD_SHARED_LIBS "Build shared libraries." ON)

if(${CMAKE_VERSION} VERSION_LESS 3.22.2)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.22.2)
endif()

project(
  GForce
  VERSION 1.0  
  LANGUAGES CXX
  DESCRIPTION "My old physics engine risen from the grave in parallel")


message(STATUS "cmake version: ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}")

add_executable(gforce apps/gforce.cpp)
target_include_directories(gforce PUBLIC apps)


