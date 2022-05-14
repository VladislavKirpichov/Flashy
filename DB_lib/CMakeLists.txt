cmake_minimum_required(VERSION 3.0.0)

project(DB_lib)

#set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-fprofile-arcs -ftest-coverage -fPIC -O0")

set(SOURCES DB_tables_page.cpp DB_tables_users.cpp DB_tables_question.cpp DB.cpp )

set(HEADERS DB.h)

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE mysqlcppconn)
