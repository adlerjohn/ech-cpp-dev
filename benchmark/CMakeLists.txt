project(ach-benchmark)

include_directories(${ech_cpp_SOURCE_DIR}/src)
link_directories(${ech_cpp_SOURCE_DIR}/src)

set(source_files
        signing.cpp
        )

add_executable(ech-benchmark main.cpp ${source_files})
target_link_libraries(ech-benchmark common)