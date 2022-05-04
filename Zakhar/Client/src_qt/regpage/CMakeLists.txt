add_library(regpage regpage.h regpage.cpp regpage.ui)
target_include_directories(regpage PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(regpage PRIVATE Qt5::Widgets)