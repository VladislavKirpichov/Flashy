add_library(userpage userpage.h userpage.cpp userpage.ui)
target_include_directories(userpage PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(userpage PRIVATE Qt5::Widgets)
