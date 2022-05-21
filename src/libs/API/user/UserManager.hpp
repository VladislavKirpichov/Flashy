//
// Created by vladislav on 14.05.22.
//

#ifndef SERVER_V0_1_USERMANAGER_HPP
#define SERVER_V0_1_USERMANAGER_HPP

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <boost/asio/strand.hpp>
#include <iostream>
#include <memory>
#include <string>

#include "JsonSerializer.h"
#include "HttpParser.h"
#include "HttpErrorCreator.hpp"
#include "Exceptions.h"


namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using error_code = boost::system::error_code;


// --------------- SAMPLE DATA ---------------
std::vector<std::vector<std::string>> USER_1 {
        {"username", "vladislav"},
        {"email", "vladislav@gmail.com"},
        {"password", "12345"},
        {"status", "student"}
};

std::vector<std::vector<std::string>> USER_2 {
        {"username", "zahar"},
        {"email", "zahar@gmail.com"},
        {"password", "12345"},
        {"status", "student"}
};

std::vector<std::vector<std::string>> USER_3 {
        {"username", "akim"},
        {"email", "akim@gmail.com"},
        {"password", "12345"},
        {"status", "student"}
};

std::vector<std::vector<std::string>> USER_4 {
        {"username", "vova"},
        {"email", "vladimir@gmail.com"},
        {"password", "12345"},
        {"status", "student"}
};
// --------------------------------------------


template<typename Body, typename Allocator, typename Send>
class UserManager : public std::enable_shared_from_this<UserManager<Body, Allocator, Send>> {
public:
    UserManager(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send);

    virtual void handle_request() = 0;

protected:
    virtual http::file_body::value_type create_body(const char* file_path) = 0;

    Send _send;
    http::request<Body, http::basic_fields<Allocator>> _request;
};

template<typename Body, typename Allocator, typename Send>
UserManager<Body, Allocator, Send>::UserManager(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send)
        : _request(std::move(req)),
          _send(std::forward<Send>(send)) {}


// --------------- GET ---------------


template<typename Body, typename Allocator, typename Send>
class GetUserManager : public UserManager<Body, Allocator, Send> {
public:
    GetUserManager(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send)
            : UserManager<Body, Allocator, Send>(std::move(req), std::forward<Send>(send)) {}

    void handle_request() final;

private:
    http::file_body::value_type create_body(const char* file_path) final;
};

// GET_UserManager, POST_UserManager, PUT_UserManager ...

template<typename Body, typename Allocator, typename Send>
void GetUserManager<Body, Allocator, Send>::handle_request() {

    http::response<http::string_body> res{ http::status::ok, this->_request.version()};
    std::vector<std::tuple<std::string, std::string>> args{};

    // Try to get args from url
    try {
        args = HttpParser::define_args(this->_request.base().target().template to_string());
    }
    catch (HttpException::InvalidArguments& ec) {
        Logger::Error(__LINE__, __FILE__, ec.what());
        HttpErrorCreator<Send>::create_bad_request_400(std::forward<Send>(this->_send), this->_request.version())->send_response();
        return;
    }

    // Set flags
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/json");
    res.keep_alive(this->_request.keep_alive());

    // Defind user by id
    if (std::get<0>(args[0]) == "id" && std::get<1>(args[0]) == "1")
        res.body() = JsonSerializer::serialize(USER_1);

    else if (std::get<0>(args[0]) == "id" && std::get<1>(args[0]) == "2")
        res.body() = JsonSerializer::serialize(USER_2);

    else if (std::get<0>(args[0]) == "id" && std::get<1>(args[0]) == "3")
        res.body() = JsonSerializer::serialize(USER_3);

    else if (std::get<0>(args[0]) == "id" && std::get<1>(args[0]) == "4")
        res.body() = JsonSerializer::serialize(USER_4);

    else
        throw APIException::UserExepction("user not found");

    res.content_length(res.body().size());

    return this->_send(std::move(res));
}

template<typename Body, typename Allocator, typename Send>
http::file_body::value_type GetUserManager<Body, Allocator, Send>::create_body(const char* file_path) {

}

#endif //SERVER_V0_1_USERMANAGER_HPP
