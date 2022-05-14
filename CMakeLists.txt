cmake_minimum_required(VERSION 3.17)
project(RecSys)

set(CMAKE_PREFIX_PATH "C:/Users/vbyko/CLionProjects/RecSys/libtorch")
find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_executable(RecSys main.cpp)
#add_subdirectory(tests)
#add_subdirectory(source)
#add_subdirectory(googletest)
#add_executable(RecSys tests/test.cpp)

target_link_libraries(RecSys "${TORCH_LIBRARIES}")
set_property(TARGET RecSys PROPERTY CXX_STANDARD 14)

#for windows vs
if (MSVC)
    file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
    add_custom_command(TARGET RecSys
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${TORCH_DLLS}
            $<TARGET_FILE_DIR:RecSys>)
endif (MSVC)