cmake_minimum_required(VERSION 3.16)
project(src)

find_package(Boost REQUIRED)
find_package(nlohmann_json REQUIRED)
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data)

# add libs
add_subdirectory(libs/API)
add_subdirectory(libs/server)

add_executable(${PROJECT_NAME} main.cpp)

# link libs
target_link_libraries(${PROJECT_NAME} PUBLIC API)
target_link_libraries(${PROJECT_NAME} PUBLIC server)

# Packages
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
