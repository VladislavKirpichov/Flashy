add_library(HTTPClient Client.h Client.cpp)
target_include_directories(HTTPClient PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
