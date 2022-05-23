cmake_minimum_required(VERSION 3.16)
project(server_v0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR};${CMAKE_MODULE_PATH}")

set(CMAKE_EXE_LINKER_FLAGS "-pthread")
add_subdirectory(server)
