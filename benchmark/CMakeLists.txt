project(ach-benchmark)

set(source_files
        bench.cpp bench.hpp)

add_executable(ech-benchmark main.cpp ${source_files})
target_link_libraries(ech-benchmark common)