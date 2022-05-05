add_library(Note Note.h Note.cpp)
target_include_directories(Note PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Note LINK_PUBLIC Block)
