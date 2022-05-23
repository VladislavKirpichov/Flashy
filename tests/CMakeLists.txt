add_executable(NewTest Test.cpp)

target_link_libraries(NewTest gtest_main)

include(GoogleTest)
gtest_discover_tests(NewTest .noArgs noArgsTests)