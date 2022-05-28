#set(BINARY ${CMAKE_PROJECT_NAME}_tst)
#
#file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)
#
#set(CMAKE_PREFIX_PATH "C:/Users/vbyko/CLionProjects/recommender_system/libtorch")
#find_package(Torch REQUIRED)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")
#
#
#set(SOURCES ${TEST_SOURCES})
#
#set(CMAKE_CXX_STANDARD 11)
#
#add_executable(${BINARY} ${TEST_SOURCES})
#add_test(NAME ${BINARY} COMMAND ${BINARY})
#target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest gmock ${TORCH_LIBRARIES})
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
###########################################################
project(test)
find_package(GTest REQUIRED)

include(GoogleTest)

add_executable(${PROJECT_NAME} Test.cpp)
add_executable(http_test http_parser.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC GTest::gtest)
target_link_libraries(${PROJECT_NAME} PUBLIC recommend)
