cmake_minimum_required(VERSION 3.22)
project(server_v0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR};${CMAKE_MODULE_PATH}")

find_package(Boost REQUIRED)
set(CMAKE_EXE_LINKER_FLAGS "-pthread")
add_subdirectory(src)

## включаем CTest
#enable_testing()
#
## в качестве фреймворка для тестирования используем GoogleTest
#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})
#
## исполняемый файл тестов
#add_executable(hello_world_test test.cpp sample_hello_world.h)
#target_link_libraries(hello_world_test ${GTEST_LIBRARIES} pthread)
#
## добавим этот файл в тестовый набор CTest
#add_test(NAME HelloWorldTest COMMAND hello_world_test)
