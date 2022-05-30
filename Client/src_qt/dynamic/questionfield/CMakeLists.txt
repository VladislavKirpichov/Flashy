add_library(questionfield questionfield.h questionfield.cpp questionfield.ui)
target_include_directories(questionfield PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(questionfield PRIVATE Qt5::Widgets)
