
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE "include")

add_executable(unit_tester main.cpp)
target_link_libraries(unit_tester Catch)