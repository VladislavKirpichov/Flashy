project(test)
find_package(GTest REQUIRED)

# include gtest script file to enable gtest_discover_tests
include(GoogleTest)

add_executable(${PROJECT_NAME} Test.cpp)

# link the target to the gtest_main library
target_link_libraries(${PROJECT_NAME} PUBLIC GTest::gtest)

# libs for tests
target_link_libraries(${PROJECT_NAME} PUBLIC Logger)
target_link_libraries(${PROJECT_NAME} PUBLIC Exceptions)
target_link_libraries(${PROJECT_NAME} PUBLIC Json)
target_link_libraries(${PROJECT_NAME} PUBLIC http_parser)
target_link_libraries(${PROJECT_NAME} PUBLIC API)
target_link_libraries(${PROJECT_NAME} PUBLIC http_response)
target_link_libraries(${PROJECT_NAME} PUBLIC src)

# add test
gtest_discover_tests(${PROJECT_NAME})