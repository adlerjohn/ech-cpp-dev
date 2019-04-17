find_package(Boost 1.53.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

set(source_files
        block.cpp
        block_header.cpp
        coin_amount.cpp
        color.cpp
        merkle.cpp
        state.cpp
        tx.cpp
        txid.cpp
        utxo.cpp
        utxoid.cpp

        )

add_library(common ${source_files})
target_link_libraries(common ${Boost_LIBRARIES} ech-crypto)