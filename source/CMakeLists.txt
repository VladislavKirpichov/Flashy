#cmake_minimum_required(VERSION 3.10)
#set(BINARY ${CMAKE_PROJECT_NAME})
#
#file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
#
#set(CMAKE_PREFIX_PATH "C:/Users/vbyko/CLionProjects/iz3/libtorch")
#find_package(Torch REQUIRED)
#include_directories(SYSTEM ${TORCH_INCLUDE_DIRS})
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")
#
#set(SOURCES Dataset.cpp Dataset.h Net.h Net.cpp RecSys.h RecSys.cpp)
#
##add_executable(${BINARY} ${SOURCES})
#add_library(${BINARY}_lib SHARED ${SOURCES})
#
#target_link_libraries(${BINARY} PRIVATE "${TORCH_LIBRARIES}")
#set_property(TARGET ${BINARY} PROPERTY CXX_STANDARD 14)
#
##for windows vs
#if (MSVC)
#    file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
#    add_custom_command(TARGET ${BINARY}
#            POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E copy_if_different
#            ${TORCH_DLLS}
#            $<TARGET_FILE_DIR:${BINARY}>)
#endif (MSVC)
#####################################################
project(recommend)

set(CMAKE_PREFIX_PATH "../torch")
find_package(Torch REQUIRED)
include_directories(SYSTEM ${TORCH_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_library(${PROJECT_NAME} SHARED RecSys.cpp Dataset.cpp Net.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${TORCH_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE "${TORCH_LIBRARIES}")

#for windows vs
if (MSVC)
    file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
    add_custom_command(TARGET ${PROJECT_NAME}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${TORCH_DLLS}
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif (MSVC)