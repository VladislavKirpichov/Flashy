project(torch)

set(TORCH_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
file(COPY ${TORCH_SRC_DIR} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/torch)

target_include_directories(${PROJECT_NAME} PUBLIC include)
