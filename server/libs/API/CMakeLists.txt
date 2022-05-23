project(API CXX)

# set executable files
set(MANAGERS IManager.hpp auth/AuthManager.hpp user/UserManager.hpp page/PageManager.hpp)
set(CREATORS auth/AuthManagerCreator.hpp user/UserManagerCreator.hpp page/PageManagerCreator.hpp)

add_library(${PROJECT_NAME} INTERFACE auth/base64.hpp ${MANAGERS} ${CREATORS})
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} auth user page)

target_link_libraries(${PROJECT_NAME} INTERFACE JSON)
target_link_libraries(${PROJECT_NAME} INTERFACE HTTP)
target_link_libraries(${PROJECT_NAME} INTERFACE DB_LIB)

# Packages
target_link_libraries(${PROJECT_NAME} INTERFACE ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} INTERFACE nlohmann_json::nlohmann_json)