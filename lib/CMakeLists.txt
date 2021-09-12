cmake_minimum_required(VERSION 3.11)

project(consolelib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

file(GLOB CL_HEADERS
    consolelib/*.h
    consolelib/*.hpp
    consolelib/exception/*.h
    consolelib/exception/*.hpp
    consolelib/function/*.h
    consolelib/function/*.hpp
    consolelib/variable/*.h
    consolelib/variable/*.hpp
    consolelib/common/*.h
    consolelib/common/*.hpp
    consolelib/generator/*.h
    consolelib/generator/*.hpp
)

add_library(consolelib INTERFACE ${CL_HEADERS})
target_include_directories(consolelib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_dependencies(consolelib hope)

set(CMAKE_INSTALL_DIRECTORY ${CMAKE_BINARY_DIR})

INSTALL(DIRECTORY consolelib/ DESTINATION ${CMAKE_INSTALL_DIRECTORY}/include/consolelib
        FILES_MATCHING PATTERN "*.h")
