cmake_minimum_required(VERSION 3.16)
project(server)

find_package(Boost REQUIRED)
find_package(nlohmann_json REQUIRED)
file(COPY entities DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data)

# add libs
add_subdirectory(DB)
add_subdirectory(entities)

#libs
add_subdirectory(libs/Logger)
add_subdirectory(libs/Exceptions)
add_subdirectory(libs/Json)
add_subdirectory(libs/http_parser)
add_subdirectory(libs/API)
add_subdirectory(libs/http_response)

add_subdirectory(src)

add_executable(${PROJECT_NAME} main.cpp)

# link libs
target_link_libraries(${PROJECT_NAME} PUBLIC DB)
target_link_libraries(${PROJECT_NAME} PUBLIC Logger)
target_link_libraries(${PROJECT_NAME} PUBLIC Exceptions)
target_link_libraries(${PROJECT_NAME} PUBLIC Json)
target_link_libraries(${PROJECT_NAME} PUBLIC http_parser)
target_link_libraries(${PROJECT_NAME} PUBLIC API)
target_link_libraries(${PROJECT_NAME} PUBLIC http_response)
target_link_libraries(${PROJECT_NAME} PUBLIC src)

# Packages
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

# --- TESTS ---
add_subdirectory(tests)
