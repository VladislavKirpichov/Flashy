project(HTTP)

add_library(${PROJECT_NAME} SHARED HttpParser.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# libs
target_link_libraries(${PROJECT_NAME} PUBLIC EXCEPTIONS LOGGER)

# Packages
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})