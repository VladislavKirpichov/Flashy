project(recommend)

set(CMAKE_PREFIX_PATH "../torch")
find_package(Torch REQUIRED)
include_directories(SYSTEM ${TORCH_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_executable(${PROJECT_NAME} RecSys.cpp Dataset.cpp Net.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${TORCH_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PUBLIC DB entities)
target_link_libraries(${PROJECT_NAME} PRIVATE "${TORCH_LIBRARIES}")