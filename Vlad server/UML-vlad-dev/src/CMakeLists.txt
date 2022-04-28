project(src)

file(GLOB SOURCES server/src/Server.cpp server/src/Listener.cpp main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES} server/src/http_connection.cpp server/include/http_connection.h server/include/http_connection.h server/src/websocket_connection.cpp server/include/websocket_connection.h)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/server/include)
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})
