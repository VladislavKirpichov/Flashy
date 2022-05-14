add_library(mainwindow mainwindow.h mainwindow.cpp mainwindow.ui)
target_include_directories(mainwindow PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(mainwindow PUBLIC mainpage userpage custompage recompage testpage)
target_link_libraries(mainwindow PRIVATE Qt5::Widgets)
