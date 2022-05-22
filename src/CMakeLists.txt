cmake_minimum_required(VERSION 3.16)
project(src)

find_package(Boost REQUIRED)
find_package(nlohmann_json REQUIRED)
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data)

# add libs
add_subdirectory(libs/DB)
add_subdirectory(libs/nlohmann)
add_subdirectory(libs/exceptions)
add_subdirectory(libs/json)
add_subdirectory(libs/http_parser)
add_subdirectory(libs/API)
add_subdirectory(libs/http_response)
add_subdirectory(libs/server)

add_executable(${PROJECT_NAME} main.cpp)

# link libs
target_link_libraries(${PROJECT_NAME} PUBLIC DB_LIB)
target_link_libraries(${PROJECT_NAME} PUBLIC EXCEPTIONS)
target_link_libraries(${PROJECT_NAME} PUBLIC JSON)
target_link_libraries(${PROJECT_NAME} PUBLIC HTTP)
target_link_libraries(${PROJECT_NAME} PUBLIC API)
target_link_libraries(${PROJECT_NAME} PUBLIC HTTP_ERRORS_RESPONSE)
target_link_libraries(${PROJECT_NAME} PUBLIC server)

# Packages
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann)
