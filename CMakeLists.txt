cmake_minimum_required(VERSION 3.20)
project(the_system VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(SRC_ROOT ${CMAKE_SOURCE_DIR}/src)

# include(${CMAKE_BINARY_DIR}/generators/conan_toolchain.cmake)

add_subdirectory(${SRC_ROOT}/domain)
