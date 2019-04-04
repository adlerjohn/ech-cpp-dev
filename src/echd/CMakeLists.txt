project(echd)

include_directories(${ech_cpp_SOURCE_DIR}/src/common)
link_directories(${ech_cpp_SOURCE_DIR}/src/common)

set(source_files
        foo.cpp
        )

add_executable(echd main.cpp ${source_files})
target_link_libraries(echd common)