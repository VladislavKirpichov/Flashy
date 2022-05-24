project(entities)

set(SRC src/Question.cpp src/Page.cpp src/User.cpp)
set(INCLUDE include/Question.h include/Page.h include/User.h)

add_library(${PROJECT_NAME} SHARED ${SRC} ${INCLUDE})
target_include_directories(${PROJECT_NAME} PUBLIC include)