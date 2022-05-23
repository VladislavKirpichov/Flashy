project(HTTP_ERRORS_RESPONSE)

set(SUCCESS http_success/HttpSuccess.hpp http_success/HttpSuccessCreator.hpp)
set(CLIENT_ERRORS http_client_errors/HttpClientErrors.hpp http_client_errors/HttpClientErrorCreator.hpp)
set(SERVER_ERRORS http_server_errors/HttpServerErrors.hpp http_server_errors/HttpServerErrorCreator.hpp)

add_library(${PROJECT_NAME} INTERFACE IHttpResponse.hpp ${SUCCESS} ${CLIENT_ERRORS} ${SERVER_ERRORS})
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} http_success http_client_errors http_server_errors)

# Packages
target_link_libraries(${PROJECT_NAME} INTERFACE ${Boost_LIBRARIES})
