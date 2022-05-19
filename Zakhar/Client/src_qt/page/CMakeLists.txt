add_library(page page.h page.cpp page.ui)
target_include_directories(page PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(page PRIVATE Qt5::Widgets)