
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE "include")

add_definitions(-DCATCH_CONFIG_CONSOLE_WIDTH=160)

include_directories(${ech_cpp_SOURCE_DIR}/src)
link_directories(${ech_cpp_SOURCE_DIR}/src)

set(source_files
        main.cpp
        common/color.cpp
        common/merkle.cpp
        common/utxo.cpp
        crypto/address.cpp
        crypto/byteset.cpp
        crypto/digest.cpp
        crypto/keys.cpp
        crypto/signature.cpp
        common/txo.cpp
        )

add_executable(unit_tester ${source_files})
target_link_libraries(unit_tester Catch common ech-crypto)