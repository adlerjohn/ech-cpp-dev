project(echd)

set(source_files
        consensus.cpp
        db.cpp
        )

add_executable(echd main.cpp ${source_files})
target_link_libraries(echd common rocksdb)