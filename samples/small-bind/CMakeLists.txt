cmake_minimum_required(VERSION 3.11)


project(small_bind_sample)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB SAMPLE_HEADERS
    *.h)

file(GLOB SAMPLE_SOURSES
    *.cpp)

add_executable(small_bind_sample ${SAMPLE_HEADERS} ${SAMPLE_SOURSES})
add_dependencies(small_bind_sample hope)

target_include_directories(small_bind_sample PUBLIC ${HOPE_INCLUDE_DIR})
target_include_directories(small_bind_sample PUBLIC ../../lib)
