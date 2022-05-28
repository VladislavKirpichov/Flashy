project(test)
find_package(GTest REQUIRED)

# include gtest script file to enable gtest_discover_tests
include(GoogleTest)

add_executable(${PROJECT_NAME} Test.cpp)
add_executable(http http_parser.cpp)
add_executable(json json.cpp)
add_executable(general general.cpp)

# link the target to the gtest_main library
target_link_libraries(${PROJECT_NAME} PUBLIC GTest::gtest)
target_link_libraries(http PUBLIC GTest::gtest)
target_link_libraries(json PUBLIC GTest::gtest)
target_link_libraries(general PUBLIC GTest::gtest)

# libs for questions
target_link_libraries(${PROJECT_NAME} PUBLIC Json)
target_link_libraries(${PROJECT_NAME} PUBLIC entities)

target_link_libraries(http PUBLIC http_parser)
target_link_libraries(json PUBLIC entities Json)
target_link_libraries(general PUBLIC entities src)

# add questions
gtest_discover_tests(${PROJECT_NAME} http json general)