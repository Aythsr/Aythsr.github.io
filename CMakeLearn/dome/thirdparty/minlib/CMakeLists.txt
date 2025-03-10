cmake_minimum_required(VERSION 3.20)

project(minlib)

set(CMAKE_CXX_STANDARD 14)

add_library(minlibFlag INTERFACE)

target_include_directories(minlibFlag INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(src)

add_subdirectory(test)
