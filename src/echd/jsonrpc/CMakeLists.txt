
set(source_files
        eth_client.cpp
        eth_client_stub.hpp
        )

add_custom_command(
        OUTPUT eth_client_stub.hpp
        COMMAND jsonrpcstub ARGS ${CMAKE_CURRENT_SOURCE_DIR}/eth.json --cpp-client=ech::EthClientStub --cpp-client-file=${CMAKE_CURRENT_SOURCE_DIR}/eth_client_stub.hpp
        MAIN_DEPENDENCY eth.json
        COMMENT "Generating ETH Stubfiles"
        VERBATIM
)

add_custom_target(
        stubs
        DEPENDS eth_client_stub.hpp
)

add_library(echjsonrpc ${source_files})
target_link_libraries(echjsonrpc jsoncpp jsonrpccpp-common jsonrpccpp-client jsonrpccpp-server jsonrpccpp-stub)