add_library(recompage recompage.h recompage.cpp recompage.ui)
target_include_directories(recompage PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(recompage PRIVATE Qt5::Widgets)
