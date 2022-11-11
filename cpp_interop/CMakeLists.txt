cmake_minimum_required (VERSION 3.8)

set (CMAKE_C_COMPILER "/usr/bin/gcc")
set (CMAKE_CXX_COMPILER "/usr/bin/g++")

project ("cpp_interop"
         DESCRIPTION "Experimental CPP RUST INTEROP"
         LANGUAGES CXX)

set (target ${PROJECT_NAME})
set (CMAKE_BUILD_TYPE Debug)
set (CMAKE_VERBOSE_MAKEFILE TRUE)

# CPP files to compile
set (proj_src interop.cpp)
# Rust lib
set (rust_lib tiny_aircraft_state)

add_library(${rust_lib} IMPORTED STATIC)
set_target_properties (
    ${rust_lib} PROPERTIES
    IMPORTED_LOCATION "/home/rmorris/development/rust_cpp_serliazation/rust_interop/target/debug/libtiny_aircraft_state.a"
    INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/../rust_interop/src")

add_executable (${target} ${proj_src})
target_compile_features (${target} PRIVATE cxx_std_17)
target_include_directories (${target} PRIVATE ${PROJECT_SOURCE_DIR}/../rust_interop/src)
target_link_libraries (${target} PRIVATE ${rust_lib} dl pthread)
