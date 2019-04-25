project(ech-benchmark)

include_directories(${ech_cpp_SOURCE_DIR}/src)
link_directories(${ech_cpp_SOURCE_DIR}/src)

add_executable(ech-benchmark-signing signing.cpp)
target_link_libraries(ech-benchmark-signing common pthread)

add_executable(ech-benchmark-consensus consensus.cpp)
target_link_libraries(ech-benchmark-consensus common pthread)