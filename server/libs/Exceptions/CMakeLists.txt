project(Exceptions)

add_library(${PROJECT_NAME} INTERFACE Exceptions.h)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} INTERFACE nlohmann_json::nlohmann_json)