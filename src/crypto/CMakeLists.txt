set(source_files
        address.cpp
        byteset.cpp
        signature.cpp
        )

add_library(ech-crypto ${source_files})
target_link_libraries(ech-crypto crypto++)