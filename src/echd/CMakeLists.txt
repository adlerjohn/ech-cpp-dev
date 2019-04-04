project(echd)

include_directories(${ech_cpp_SOURCE_DIR}/src/common)
link_directories(${ech_cpp_SOURCE_DIR}/src/common)

add_executable(echd main.cpp foo.cpp)
target_link_libraries(echd common)