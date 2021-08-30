cmake_minimum_required(VERSION 3.11)

project(small_bind_sample)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB SAMPLE_HEADERS
    *.h)
	
file(GLOB SAMPLE_SOURSES
    *.cpp)

add_executable(small_bind_sample ${SAMPLE_HEADERS} ${SAMPLE_SOURSES})
target_include_directories(small_bind_sample PUBLIC ../../lib)
target_link_libraries(small_bind_sample consolelib)