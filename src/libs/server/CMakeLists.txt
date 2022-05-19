project(server)

set(SRC src/Listener.cpp
        src/Server.cpp)
set(INCLUDE include/API_Gateway.hpp
            include/Logger.hpp
            include/RequestHandler.hpp
            include/Server.h
            include/Listener.h
            include/Errors.hpp)

add_library(server SHARED ${SRC} ${INCLUDE})
target_include_directories(${PROJECT_NAME}
    PRIVATE
        # where the library itself will look for its internal headers
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PUBLIC
        # where top-level project will look for the library's public headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        # where external projects will look for the library's public headers
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(${PROJECT_NAME} PUBLIC API)
target_link_libraries(${PROJECT_NAME} PUBLIC HTTP)

# Packages
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)