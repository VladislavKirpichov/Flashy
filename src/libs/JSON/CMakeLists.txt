project(JSON)

add_library(${PROJECT_NAME} SHARED JsonSerializer.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)