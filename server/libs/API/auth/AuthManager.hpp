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
private:
    std::vector<std::tuple<std::string, std::string>> get_args();
};

template<typename Body, typename Allocator, typename Send>
void AuthManager<Body, Allocator, Send>::auth_user() {
    std::string url_path = this->get_request_target();
    // decode part of url thar starts from ?
//    url_path = base64_decode(std::string(std::find(url_path.begin(), url_path.end(), '?'), url_path.end()), true);
    std::vector<std::tuple<std::string, std::string>> args{};

    // Try to get args from url
    try {
        args = HttpParser::define_args(url_path);
    }
    catch (HttpException::InvalidArguments& ec) {
        Logger::Error(__LINE__, __FILE__, ec.what());
        HttpClientErrorCreator<Send>::create_bad_request_400(std::forward<Send>(this->get_send()), this->get_request_version())->send_response();
        return;
    }

    // TODO: взять данные о пользователе из БД и сверить пароль с тем, что пришел
    if (std::get<0>(args[0]) == "username" && std::get<1>(args[0]) == "user1" &&
        std::get<0>(args[1]) == "password" && std::get<1>(args[1]) == "123")
        HttpSuccessCreator<Send>::create_ok_200(std::move(this->get_send()), this->get_request_version())->send_response();
    else
        HttpClientErrorCreator<Send>::create_unauthorized_401(std::move(this->get_send()), this->get_request_version())->send_response();
}

template<typename Body, typename Allocator, typename Send>
std::vector<std::tuple<std::string, std::string>> AuthManager<Body, Allocator, Send>::get_args() {
    return std::vector<std::tuple<std::string, std::string>>();
}

#endif //SERVER_V0_1_AUTHMANAGER_HPP
