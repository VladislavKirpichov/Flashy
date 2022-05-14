add_library(custompage custompage.h custompage.cpp custompage.ui)
target_include_directories(custompage PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(custompage PUBLIC recompage testpage)
target_link_libraries(custompage PRIVATE Qt5::Widgets)
