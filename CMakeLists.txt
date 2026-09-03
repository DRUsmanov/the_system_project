cmake_minimum_required(VERSION 3.20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(the_system VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(SRC_ROOT ${CMAKE_SOURCE_DIR}/src)

include(${CMAKE_BINARY_DIR}/generators/conan_toolchain.cmake)

find_package(Boost REQUIRED)
find_package(libpqxx REQUIRED)
find_package(jwt-cpp REQUIRED)

add_subdirectory(${SRC_ROOT}/utils)
add_subdirectory(${SRC_ROOT}/domain)
add_subdirectory(${SRC_ROOT}/application)
add_subdirectory(${SRC_ROOT}/infrastructure)

add_executable(the_system main.cpp)

target_include_directories(the_system PRIVATE ${SRC_ROOT})
target_link_libraries(the_system PUBLIC infrastructure)
