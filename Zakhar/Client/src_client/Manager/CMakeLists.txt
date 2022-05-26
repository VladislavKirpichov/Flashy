add_library(Manager Manager.h Manager.cpp)
target_include_directories(Manager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Manager LINK_PUBLIC HTTPClient Serializer Page User Question)