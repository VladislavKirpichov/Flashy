project(DB)

#set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-fprofile-arcs -ftest-coverage -fPIC -O0")

set(CMAKE_CXX_FLAGS "-fPIC")
set(SOURCES ../entities/src/Page.cpp ../entities/src/User.cpp ../entities/src/Question.cpp DB.cpp )

set(HEADERS DB.h)

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE mysqlcppconn)
