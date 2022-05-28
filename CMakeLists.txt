cmake_minimum_required(VERSION 3.10)
project(project)

cmake_minimum_required(VERSION 3.10)
set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(CMAKE_PREFIX_PATH "C:/Users/vbyko/CLionProjects/iz3/libtorch")
find_package(Torch REQUIRED)
include_directories(SYSTEM ${TORCH_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

#set(SOURCES main.cpp Net.h Net.cpp Dataset.h Dataset.cpp RecSys.cpp RecSys.h)
#add_executable(${BINARY} ${SOURCES})

target_link_libraries(${BINARY} PRIVATE "${TORCH_LIBRARIES}")
set_property(TARGET ${BINARY} PROPERTY CXX_STANDARD 14)

#for windows vs
if (MSVC)
    file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
    add_custom_command(TARGET ${BINARY}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${TORCH_DLLS}
            $<TARGET_FILE_DIR:${BINARY}>)
endif (MSVC)