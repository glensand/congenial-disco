cmake_minimum_required(VERSION 3.11)

project(congenial-disco-main)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)
include("ext/hope.cmake")

add_subdirectory(test)
add_subdirectory(samples/small-bind)
add_subdirectory(lib)