project(LOGGER)

add_library(${PROJECT_NAME} INTERFACE Logger.hpp)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
