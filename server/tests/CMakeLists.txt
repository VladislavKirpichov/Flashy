project(test)
find_package(GTest REQUIRED)

# include gtest script file to enable gtest_discover_tests
include(GoogleTest)

add_executable(${PROJECT_NAME} Test.cpp)
add_executable(http_test http_parser.cpp)

# link the target to the gtest_main library
target_link_libraries(${PROJECT_NAME} PUBLIC GTest::gtest)
target_link_libraries(http_test PUBLIC GTest::gtest)

# libs for question
target_link_libraries(${PROJECT_NAME} PUBLIC Json)
target_link_libraries(${PROJECT_NAME} PUBLIC entities)

target_link_libraries(http_test PUBLIC http_parser)

# add question
gtest_discover_tests(${PROJECT_NAME} http_test)