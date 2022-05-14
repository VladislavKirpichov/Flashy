project(src)

file(GLOB SOURCES server/src/Server.cpp server/src/Listener.cpp main.cpp)
file(GLOB INDEX "index.html")
file(COPY server/include/doc_root/${INDEX} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/doc_root)

add_executable(${PROJECT_NAME} ${SOURCES} server/include/API_Gateway.hpp server/include/API_Gateway.hpp server/src/websocket_connection.cpp server/include/websocket_connection.h server/include/Logger.hpp)

# API


target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/server/include server/include/API/page server/include/API/user server/include/API/auth)
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})
