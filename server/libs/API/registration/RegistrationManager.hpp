//
// Created by vladislav on 26.05.22.
//

#ifndef SERVER_V0_1_REGISTRATIONMANAGER_HPP
#define SERVER_V0_1_REGISTRATIONMANAGER_HPP

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <boost/asio/strand.hpp>
#include <iostream>
#include <memory>
#include <string>

#include <cppconn/exception.h>

#include "IManager.hpp"
#include "HttpSuccessCreator.hpp"
#include "HttpClientErrorCreator.hpp"
#include "HttpParser.h"
#include "Logger.hpp"
#include "Exceptions.h"
#include "JsonSerializer.h"
#include "User.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using error_code = boost::system::error_code;

template<typename Body, typename Allocator, typename Send>
class RegistrationManager : public IManager<Body, Allocator, Send> {
public:
    using IManager<Body, Allocator, Send>::IManager;

    void register_user();

private:
    void create_new_user(std::unordered_map<std::string, std::string>& json);
};

template<typename Body, typename Allocator, typename Send>
void RegistrationManager<Body, Allocator, Send>::create_new_user(std::unordered_map<std::string, std::string>& json) {
    User user {json.at("login"), json.at("name"), json.at("password"), json.at("email"), json.at("status")};
    user.add_user();
    user.user_close_connect();
}

template<typename Body, typename Allocator, typename Send>
void RegistrationManager<Body, Allocator, Send>::register_user() {
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

    try {
        if (!User::find_user_nick(args.at("login"), args.at("password"))) {
            std::unordered_map<std::string, std::string> json = JsonSerializer::deserialize(this->get_request_body_data());
            create_new_user(json);
        }
        else
            HttpClientErrorCreator<Send>::create_forbidden_403(std::move(this->get_send()), this->get_request_version())->send_response();
    }
    catch (std::out_of_range& ec) {
        HttpClientErrorCreator<Send>::create_bad_request_400(std::move(this->get_send()), this->get_request_version())->send_response();
        return;
    }
    // TODO: исправить с 404
    catch (sql::SQLException& ec) {
        HttpClientErrorCreator<Send>
        ::create_not_found_404(std::move(this->get_send()), this->get_request_version())->send_response();
        return;
    }
    catch (JsonException::JsonException& ec) {
        HttpClientErrorCreator<Send>::create_bad_request_400(std::move(this->get_send()), this->get_request_version())->send_response();
        return;
    }

    return HttpSuccessCreator<Send>::create_ok_200(std::move(this->get_send()), this->get_request_version())->send_response();
}

#endif //SERVER_V0_1_REGISTRATIONMANAGER_HPP
