find_package(Boost 1.53.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

set(source_files
        coin_amount.cpp
        color.cpp
        state.cpp
        tx.cpp
        utxo.cpp
        block.cpp
        block_header.cpp
        txid.cpp
        utxoid.cpp
        )

add_library(common ${source_files})
target_link_libraries(common ${Boost_LIBRARIES} ech-crypto)