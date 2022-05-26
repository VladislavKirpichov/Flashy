add_library(questioneditor questioneditor.h questioneditor.cpp)
target_include_directories(questioneditor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(questioneditor PRIVATE Qt5::Widgets)