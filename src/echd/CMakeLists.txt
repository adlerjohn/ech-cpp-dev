project(echd)

set(source_files
        foo.cpp
        db.cpp
        )

add_executable(echd main.cpp ${source_files})
target_link_libraries(echd common rocksdb)