project(http_parser)

add_library(${PROJECT_NAME} SHARED HttpParser.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# libs
target_link_libraries(${PROJECT_NAME} PUBLIC Exceptions Logger)

# Packages
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})