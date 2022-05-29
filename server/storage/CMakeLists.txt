project(storage)

file(GLOB SRC_DIR data/hello.txt)

set(CMAKE_CXX_FLAGS "-fconcepts")

file(COPY ${SRC_DIR} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data)
# add_executable(${PROJECT_NAME} Storage.cpp)
add_library(${PROJECT_NAME} SHARED Storage.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE Exceptions)