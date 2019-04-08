project(echd)

include_directories(${ech_cpp_SOURCE_DIR}/src)
link_directories(${ech_cpp_SOURCE_DIR}/src)

set(source_files
        foo.cpp
        db.cpp
        )

add_executable(echd main.cpp ${source_files})
target_link_libraries(echd common rocksdb)