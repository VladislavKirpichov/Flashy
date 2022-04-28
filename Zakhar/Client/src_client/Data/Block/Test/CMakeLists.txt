add_library(Test Test.h Test.cpp)
target_include_directories(Test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Test PUBLIC Block)
