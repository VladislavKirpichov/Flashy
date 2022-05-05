add_library(Block Block.h Block.cpp)
target_include_directories(Block PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(Test)
add_subdirectory(Text_field)