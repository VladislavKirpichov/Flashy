cmake_minimum_required(VERSION 3.11)
project(API)

add_library(${PROJECT_NAME} SHARED auth/AuthManagerCreator.hpp user/UserManagerCreator.hpp page/PageManagerCreator.hpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
