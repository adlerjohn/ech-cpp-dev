
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE "include")

include_directories(${ech_cpp_SOURCE_DIR}/src)
link_directories(${ech_cpp_SOURCE_DIR}/src)

add_executable(unit_tester main.cpp common/utxo.cpp)
target_link_libraries(unit_tester Catch common)