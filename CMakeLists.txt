cmake_minimum_required(VERSION 3.10)
project(ech_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-Wall -fpermissive")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)
add_subdirectory(benchmark)

####################
# Testing
####################

add_subdirectory(test)
enable_testing()
add_test(NAME unit_tests COMMAND unit_tester)