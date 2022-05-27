project(src)

set(SRC src/Listener.cpp
        src/Server.cpp)

set(INCLUDE include/API_Gateway.hpp
            include/RequestHandler.hpp
            include/Server.h
            include/Listener.h)

add_library(src SHARED ${SRC} ${INCLUDE})
target_include_directories(${PROJECT_NAME}
    PRIVATE
        # where the library itself will look for its internal headers
        include
    PUBLIC
        # where top-level project will look for the library's public headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        # where external projects will look for the library's public headers
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# libs
target_link_libraries(${PROJECT_NAME} PUBLIC API http_parser http_response Logger)

# Packages
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)