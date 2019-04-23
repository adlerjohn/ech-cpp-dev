find_package(Boost 1.53.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

set(source_files
        block.cpp
        block_header.cpp
        color.cpp
        deposit.cpp
        input.cpp
        merkle.cpp
        outpoint.cpp
        state.cpp
        tx.cpp
        txo.cpp
        utxo.cpp
        utxoid.cpp
        )

add_library(common ${source_files})
target_link_libraries(common ${Boost_LIBRARIES} ech-crypto)