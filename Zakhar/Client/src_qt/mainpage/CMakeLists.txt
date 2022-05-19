add_library(mainpage mainpage.h mainpage.cpp mainpage.ui)
target_include_directories(mainpage PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(mainpage PUBLIC custompage page)
target_link_libraries(mainpage PRIVATE Qt5::Widgets)
