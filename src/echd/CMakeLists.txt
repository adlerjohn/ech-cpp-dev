project(echd)

add_subdirectory(jsonrpc)

set(source_files
        consensus.cpp
        db.cpp
        mempool.cpp
        state.cpp
        transition.cpp
        )

add_library(echd-lib ${source_files})
target_link_libraries(echd-lib common echjsonrpc rocksdb)

add_executable(echd main.cpp)
target_link_libraries(echd echd-lib)