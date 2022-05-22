//
// Created by vladislav on 14.05.22.
//

#ifndef SERVER_V0_1_AUTHMANAGER_HPP
#define SERVER_V0_1_AUTHMANAGER_HPP

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <boost/asio/strand.hpp>
#include <iostream>
#include <memory>
#include <string>

#include "base64.hpp"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using error_code = boost::system::error_code;

template<typename Body, typename Allocator, typename Send>
class AuthManager {
public:
    AuthManager(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send)
            : _request(std::move(req)),
              _send(std::forward<Send>(send)) {}

    void auth_user();
    void send_success() const;
    void send_failure();


    Send _send;
    http::request<Body, http::basic_fields<Allocator>> _request;
};

template<typename Body, typename Allocator, typename Send>
void AuthManager<Body, Allocator, Send>::auth_user() {
    std::string url_path = this->_request.base().target().template to_string();
    // decode part of url thar starts from ?
    url_path = base64_decode(std::string(std::find(url_path.begin(), url_path.end(), '?'), url_path.end()), true);
    std::vector<std::tuple<std::string, std::string>> args{};

    // Try to get args from url
    try {
        args = HttpParser::define_args(url_path);
    }
    catch (HttpException::InvalidArguments& ec) {
        Logger::Error(__LINE__, __FILE__, ec.what());
        HttpClientErrorCreator<Send>::create_bad_request_400(std::forward<Send>(this->_send), this->_request.version())->send_response();
        return;
    }

    // TODO: взять данные о пользователе из БД и сверить пароль с тем, что пришел
    if (std::get<0>(args[0]) == "username" && std::get<1>(args[0]) == "user1" &&
        std::get<0>(args[1]) == "password" && std::get<1>(args[1]) == "123")
        send_success();
    else
        send_failure();
}

template<typename Body, typename Allocator, typename Send>
void AuthManager<Body, Allocator, Send>::send_success() const {
    http::response<http::string_body> res{http::status::ok, this->_request.version()};

    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/text");
    res.keep_alive(this->_request.keep_alive());

    res.body() = "ok";
    return this->_send(std::move(res));
}

template<typename Body, typename Allocator, typename Send>
void AuthManager<Body, Allocator, Send>::send_failure() {
    HttpClientErrorCreator<Send>::create_unauthorized_401(std::forward<Send>(this->_send), this->_request.version())->send_response();
}


#endif //SERVER_V0_1_AUTHMANAGER_HPP
