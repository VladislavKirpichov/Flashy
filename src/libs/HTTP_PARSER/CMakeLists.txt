project(HTTP)

add_library(${PROJECT_NAME} SHARED HttpParser.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC ${Boost_LIBRARIES})