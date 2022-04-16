cmake_minimum_required(VERSION 3.0)
project(boost-server)


set(SOURCE main.cpp)
set(BOOST_ROOT "$HOME/dev/boost_1_72_0")
set(CMAKE_EXE_LINKER_FLAGS "-L /usr/lib -lboost_system -lboost_thread -lphtread")

include_directories(include)
add_executable(${PROJECT_NAME} ${SOURCE})