add_library(Serializer Serializer.h Serializer.cpp)
target_include_directories(Serializer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Serializer LINK_PUBLIC User Page Question)
