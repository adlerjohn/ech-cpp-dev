include_directories(${ech_cpp_SOURCE_DIR}/src)
link_directories(${ech_cpp_SOURCE_DIR}/src)

add_subdirectory(crypto)
add_subdirectory(common)
add_subdirectory(echd)
#add_subdirectory(ech-cli)