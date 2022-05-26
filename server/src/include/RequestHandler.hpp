//
// Created by vladislav on 13.05.22.
//

#ifndef SERVER_V0_1_REQUESTHANDLER_H
#define SERVER_V0_1_REQUESTHANDLER_H

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio/detail/reactive_socket_service_base.hpp>
#include <boost/config.hpp>
#include <iostream>
#include <memory>
#include <string>

#include "../../Logger/Logger.hpp"

#include "HttpParser.h"
#include "HttpClientErrorCreator.hpp"

#include "PageManagerCreator.hpp"
#include "UserManagerCreator.hpp"
#include "AuthManagerCreator.hpp"
#include "RegistrationManagerCreator.hpp"


namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using error_code = boost::system::error_code;


// Interface for handlers
template<typename Body, typename Allocator, typename Send>
class RequestHandler: public std::enable_shared_from_this<RequestHandler<Body, Allocator, Send>> {
public:
    RequestHandler(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send)
        : _request(std::move(req)), _send(send) {}

    virtual void process_request() = 0;

    std::string_view _url_path;
    http::request<Body, http::basic_fields<Allocator>> _request;
    Send _send;

protected:
    void define_type_by_path();
};

template<typename Body, typename Allocator, typename Send>
void RequestHandler<Body, Allocator, Send>::define_type_by_path() {
    // Try to read url path
    try {
        this->_url_path = HttpParser::define_page_type(this->_request.base().target().template to_string());
    }
    catch (HttpException::InvalidArguments& ec) {
        // handle bad_request
        Logger::Info(__LINE__, __FILE__, "bad_request");
        HttpClientErrorCreator<Send>::create_bad_request_400(std::forward<Send>(this->_send), this->_request.version())->send_response();
        return;
    }
    catch (...) {
        // some other error
        Logger::Info(__LINE__, __FILE__, "url_path_error");
        throw ServerException::RequestHandlerException("HttpParser Exception");
    }
}


// GET HANDLER


template<typename Body, typename Allocator, typename Send>
class GetHandler : public RequestHandler<Body, Allocator, Send> {
public:
    using RequestHandler<Body, Allocator, Send>::RequestHandler;

    void process_request() final;
};

template<typename Body, typename Allocator, typename Send>
void GetHandler<Body, Allocator, Send>::process_request() {
    this->define_type_by_path();

    // Send a request to the desired manager
    try {
        if (this->_url_path == "registration")
            RegistrationManagerCreator<Body, Allocator, Send>
            ::create_RegistrationManager(std::move(this->_request), std::forward<Send>(this->_send))->handle_request();
        else if (this->_url_path == "auth")
            AuthManagerCreator<Body, Allocator, Send>
            ::create_AuthManager(std::move(this->_request), std::forward<Send>(this->_send))->auth_user();
        if (this->_url_path == "page")
            PageManagerCreator<Body, Allocator, Send>
            ::create_GetPageManager(std::move(this->_request), std::forward<Send>(this->_send))->handle_request();
        else if (this->_url_path == "user")
            UserManagerCreator<Body, Allocator, Send>
            ::create_GetUserManager(std::move(this->_request), std::forward<Send>(this->_send))->handle_request();
    }
    catch (APIException::APIException& ec) {
        HttpClientErrorCreator<Send>::create_bad_request_400(std::forward<Send>(this->_send), this->_request.version())->send_response();
    }
    catch (...) {
        throw ServerException::RequestHandlerException("Not API exception in RequestHandler");
    }
}


// PUT HANDLER


template<typename Body, typename Allocator, typename Send>
class PutHandler : public RequestHandler<Body, Allocator, Send> {
public:
    using RequestHandler<Body, Allocator, Send>::RequestHandler;

    void process_request() final;
};

template<typename Body, typename Allocator, typename Send>
void PutHandler<Body, Allocator, Send>::process_request() {
    this->define_type_by_path();

    // Send a request to the desired manager
    try {
        if (this->_url_path == "page")
            PageManagerCreator<Body, Allocator, Send>
            ::create_PutPageManager(std::move(this->_request), std::forward<Send>(this->_send))->handle_request();
        else if (this->_url_path == "user")
            UserManagerCreator<Body, Allocator, Send>
            ::create_PutUserManager(std::move(this->_request), std::forward<Send>(this->_send))->handle_request();
    }
    catch (APIException::APIException& ec) {
        HttpClientErrorCreator<Send>::create_bad_request_400(std::forward<Send>(this->_send), this->_request.version())->send_response();
    }
    catch (...) {
        throw ServerException::RequestHandlerException("Not API exception in RequestHandler");
    }
}


// POST HANDLER


template<typename Body, typename Allocator, typename Send>
class PostHandler : public RequestHandler<Body, Allocator, Send> {
public:
    using RequestHandler<Body, Allocator, Send>::RequestHandler;

    void process_request() final;
};

template<typename Body, typename Allocator, typename Send>
void PostHandler<Body, Allocator, Send>::process_request() {
    this->define_type_by_path();

    // Send a request to the desired manager
    try {
        if (this->_url_path == "page")
            PageManagerCreator<Body, Allocator, Send>
            ::create_PostPageManager(std::move(this->_request), std::forward<Send>(this->_send))->handle_request();
        else if (this->_url_path == "user")
            UserManagerCreator<Body, Allocator, Send>
            ::create_PostUserManager(std::move(this->_request), std::forward<Send>(this->_send))->handle_request();
    }
    catch (APIException::APIException& ec) {
        HttpClientErrorCreator<Send>::create_bad_request_400(std::forward<Send>(this->_send), this->_request.version())->send_response();
    }
    catch (...) {
        throw ServerException::RequestHandlerException("Not API exception in RequestHandler");
    }
}

#endif //SERVER_V0_1_REQUESTHANDLER_H
