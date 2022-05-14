add_library(testpage testpage.h testpage.cpp testpage.ui)
target_include_directories(testpage PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(testpage PRIVATE Qt5::Widgets)