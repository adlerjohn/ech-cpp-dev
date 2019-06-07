project(echd)

set(source_files
        consensus.cpp
        db.cpp
        mempool.cpp
        state.cpp
        transition.cpp
        )

add_library(echd-lib ${source_files})
target_link_libraries(echd-lib common rocksdb)

add_executable(echd main.cpp)
target_link_libraries(echd echd-lib)