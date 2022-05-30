add_library(Page Page.h Page.cpp)
target_include_directories(Page PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Page LINK_PUBLIC Question User)
