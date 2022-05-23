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

#include "IManager.hpp"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using error_code = boost::system::error_code;

template<typename Body, typename Allocator, typename Send>
class AuthManager : public IManager<Body, Allocator, Send> {
public:
    using IManager<Body, Allocator, Send>::IManager;

    void auth_user();
};

template<typename Body, typename Allocator, typename Send>
void AuthManager<Body, Allocator, Send>::auth_user() {
    std::string url_path = this->get_request_target();
    std::unordered_map<std::string, std::string> args{};

    // Try to get args from url
    try {
        args = HttpParser::define_args_map(url_path);
    }
    catch (HttpException::InvalidArguments& ec) {
        Logger::Error(__LINE__, __FILE__, ec.what());
        HttpClientErrorCreator<Send>::create_bad_request_400(std::forward<Send>(this->get_send()), this->get_request_version())->send_response();
        return;
    }

    // TODO: взять данные о пользователе из БД и сверить пароль с тем, что пришел
    try {
        if (args.at("login") == "user1" && args.at("password") == "123")
            HttpSuccessCreator<Send>::create_ok_200(std::move(this->get_send()), this->get_request_version())->send_response();
        else
            HttpClientErrorCreator<Send>::create_unauthorized_401(std::move(this->get_send()), this->get_request_version())->send_response();
    }
    catch (std::out_of_range& ec) {
        HttpClientErrorCreator<Send>::create_bad_request_400(std::move(this->get_send()), this->get_request_version())->send_response();
    }
}

#endif //SERVER_V0_1_AUTHMANAGER_HPP
