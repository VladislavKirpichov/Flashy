project(HTTP_ERRORS_RESPONSE)

add_library(${PROJECT_NAME} INTERFACE HttpErrors.hpp HttpErrorCreator.hpp)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Packages
target_link_libraries(${PROJECT_NAME} INTERFACE ${Boost_LIBRARIES})
