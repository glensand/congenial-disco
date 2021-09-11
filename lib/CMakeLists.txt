cmake_minimum_required(VERSION 3.11)

project(consolelib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

file(GLOB CL_HEADERS
    consolelib/*.h
    consolelib/exception/*.h
    consolelib/function/*.h
    consolelib/variable/*.h
    consolelib/common/*.h
    consolelib/generator/*.h
)

file(GLOB CL_SOURSES
    consolelib/*.cpp
    consolelib/exception/*.cpp
    consolelib/function/*.cpp
    consolelib/variable/*.cpp
    consolelib/generator/*.cpp
)

add_library(consolelib STATIC ${CL_HEADERS} ${CL_SOURSES})
target_include_directories(consolelib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(consolelib PUBLIC PUBLIC ${HOPE_INCLUDE_DIR})

add_dependencies(consolelib hope)
set(CMAKE_INSTALL_DIRECTORY ${CMAKE_BINARY_DIR})

INSTALL(DIRECTORY consolelib/ DESTINATION ${CMAKE_INSTALL_DIRECTORY}/include/consolelib
        FILES_MATCHING PATTERN "*.h")
