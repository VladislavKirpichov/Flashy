add_library(notebutton notebutton.h notebutton.cpp)
target_include_directories(notebutton PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(notebutton PRIVATE Qt5::Widgets)
