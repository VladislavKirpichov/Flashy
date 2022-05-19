project(API CXX)

# set executable files
set(MANAGERS auth/AuthManager.hpp user/UserManager.hpp page/PageManager.hpp)
set(CREATORS auth/AuthManagerCreator.hpp user/UserManagerCreator.hpp page/PageManagerCreator.hpp)
set(JSON JsonSerializer.cpp JsonSerializer.hpp)

add_library(API SHARED ${JSON} ${MANAGERS} ${CREATORS})
target_include_directories(${PROJECT_NAME} PUBLIC auth user page)

# Packages
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)