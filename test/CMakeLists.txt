
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE "include")

add_definitions(-DCATCH_CONFIG_CONSOLE_WIDTH=160)

include_directories(${ech_cpp_SOURCE_DIR}/src)
link_directories(${ech_cpp_SOURCE_DIR}/src)

set(source_files
        main.cpp
        common/block.cpp
        common/block_header.cpp
        common/color.cpp
        common/deposit.cpp
        common/input.cpp
        common/merkle.cpp
        common/outpoint.cpp
        common/tx.cpp
        common/txo.cpp
        common/utxo.cpp
        common/utxoid.cpp
        crypto/address.cpp
        crypto/byteset.cpp
        crypto/digest.cpp
        crypto/keys.cpp
        crypto/signature.cpp
        echd/jsonrpc/eth_client.cpp
        echd/consensus.cpp
        echd/state.cpp
        )

add_executable(unit_tester ${source_files})
target_link_libraries(unit_tester Catch echd-lib common ech-crypto)