cmake_minimum_required(VERSION 3.11)

project(consolelib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB CL_HEADERS
    consolelib/*.h
    consolelib/exception/*.h
    consolelib/function/*.h
    consolelib/variable/*.h
)

file(GLOB CL_SOURSES
    consolelib/*.cpp
    consolelib/exception/*.cpp
    consolelib/function/*.cpp
    consolelib/variable/*.cpp
)

add_library(consolelib STATIC ${CL_HEADERS} ${CL_SOURSES})
target_include_directories(consolelib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(consolelib PUBLIC ../ext)