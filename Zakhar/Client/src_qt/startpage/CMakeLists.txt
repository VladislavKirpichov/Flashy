add_library(startpage startpage.h startpage.cpp startpage.ui)
target_include_directories(startpage PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(startpage PUBLIC mainwindow regpage)
target_link_libraries(startpage PRIVATE Qt5::Widgets)
