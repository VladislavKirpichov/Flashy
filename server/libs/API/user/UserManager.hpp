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

#include "Logger.hpp"
#include "IManager.hpp"
#include "JsonSerializer.h"
#include "HttpParser.h"
#include "HttpSuccessCreator.hpp"
#include "HttpClientErrorCreator.hpp"
#include "HttpServerErrorCreator.hpp"
#include "Exceptions.h"
#include <cppconn/exception.h>
#include "User.h"



namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using error_code = boost::system::error_code;


// TODO: Добавить классы POST, PUT, DELETE

template<typename Body, typename Allocator, typename Send>
class IUserManager : public IManager<Body, Allocator, Send> {
public:
    using IManager<Body, Allocator, Send>::IManager;
    virtual void handle_request() = 0;

protected:
    virtual void set_flags(http::response<http::string_body>& response);
    // virtual void find_user_in_db();
};

template<typename Body, typename Allocator, typename Send>
void IUserManager<Body, Allocator, Send>::set_flags(http::response<http::string_body>& response) {
    response.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    response.set(http::field::content_type, "text/text");
    response.keep_alive(this->get_request_keep_alive());
    response.content_length(response.body().size());
}


/*
 * The GET method requests a representation of the specified resource.
 * Requests using GET should only retrieve entities and should have no other effect.
*/


template<typename Body, typename Allocator, typename Send>
class GetUserManager : public IUserManager<Body, Allocator, Send> {
public:
    using IUserManager<Body, Allocator, Send>::IUserManager;
    void handle_request() final;

protected:
    void set_flags(http::response<http::string_body>&) override;
};

template<typename Body, typename Allocator, typename Send>
void GetUserManager<Body, Allocator, Send>::set_flags(http::response<http::string_body>& response) {
    response.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    response.set(http::field::content_type, "text/json");
    response.keep_alive(this->get_request_keep_alive());
    response.content_length(response.body().size());
}

template<typename Body, typename Allocator, typename Send>
void GetUserManager<Body, Allocator, Send>::handle_request() {
    http::response<http::string_body> response{ http::status::ok, this->get_request_version()};
    std::unordered_map<std::string, std::string> args{};

    // Try to get args from url
    try {
        args = HttpParser::define_args_map(this->get_request_target());
        // args = this->get_args_url();
    }
    catch (HttpException::InvalidArguments& ec) {
        Logger::Error(__LINE__, __FILE__, ec.what());
        HttpClientErrorCreator<Send>::create_bad_request_400(std::forward<Send>(this->get_send()), this->get_request_version())->send_response();
        return;
    }

    // Find user by id
    // TODO: взять информацию о пользователе из БД
    // this->find_user_in_db();

    try {
        User temp_user{args.at("login")};
        if (temp_user.get_pass() == args.at("password"))
            response.body() = JsonSerializer::serialize_user(temp_user);
        else
            throw APIException::UserException();
    }
    catch (JsonException::JsonException& ec) {
        HttpServerErrorCreator<Send>
                ::create_service_unavailable_503(std::move(this->get_send()), this->get_request_version())->send_response();
        return;
    }
    // if in request we have no "login"
    catch (std::out_of_range& ec) {
        HttpClientErrorCreator<Send>
                ::create_bad_request_400(std::move(this->get_send()), this->get_request_version())->send_response();
        return;
    }
    catch (APIException::UserException& ec) {
        HttpClientErrorCreator<Send>
                ::create_not_found_404(std::move(this->get_send()), this->get_request_version())->send_response();
        return;
    }
    catch (sql::SQLException& ec) {
        HttpClientErrorCreator<Send>
        ::create_not_found_404(std::move(this->get_send()), this->get_request_version())->send_response();
        return;
    }

    this->set_flags(response);

    return this->get_send()(std::move(response));
}


// POST


template<typename Body, typename Allocator, typename Send>
class PostUserManager : public IUserManager<Body, Allocator, Send> {
public:
    using IUserManager<Body, Allocator, Send>::IUserManager;
    void handle_request() final;

private:
    void set_user_fields(const std::string& login, const std::unordered_map<std::string, std::string>& json);
};

template<typename Body, typename Allocator, typename Send>
void PostUserManager<Body, Allocator, Send>::set_user_fields(const std::string& login, const std::unordered_map<std::string, std::string>& json) {
    User user{login};

    if (json.find("login") != json.end())
        user.update_nick(json.at("login"));
    if (json.find("email") != json.end())
        user.update_email(json.at("email"));
    if (json.find("password") != json.end())
        user.update_pass(json.at("password"));
    if (json.find("status") != json.end())
        user.update_status(json.at("status"));
}

template<typename Body, typename Allocator, typename Send>
void PostUserManager<Body, Allocator, Send>::handle_request() {
    std::unordered_map<std::string, std::string> args{};
    // Try to get args from url
    try {
        args = HttpParser::define_args_map(this->get_request_target());
        // args = this->get_args_url();
    }
    catch (HttpException::InvalidArguments& ec) {
        Logger::Error(__LINE__, __FILE__, ec.what());
        HttpClientErrorCreator<Send>::create_bad_request_400(std::forward<Send>(this->get_send()), this->get_request_version())->send_response();
        return;
    }

    try {
        if (User::find_user_nick(args.at("login"), args.at("password"))) {
            std::unordered_map<std::string, std::string> json = JsonSerializer::deserialize(this->get_request_body_data());
            set_user_fields(args.at("login"), json);
            return HttpSuccessCreator<Send>::create_ok_200(std::move(this->get_send()), this->get_request_version())->send_response();
        }
        else
            return HttpClientErrorCreator<Send>::create_not_found_404(std::move(this->get_send()), this->get_request_version())->send_response();
    }
    catch (JsonException::JsonException& ec) {
        return HttpServerErrorCreator<Send>::create_service_unavailable_503(std::move(this->get_send()), this->get_request_version())->send_response();
    }
}


// DELETE


template<typename Body, typename Allocator, typename Send>
class DeleteUserManager : public IUserManager<Body, Allocator, Send> {
public:
    using IUserManager<Body, Allocator, Send>::IUserManager;
    void handle_request() final;
};

template<typename Body, typename Allocator, typename Send>
void DeleteUserManager<Body, Allocator, Send>::handle_request() {
    // get args from url
    std::unordered_map<std::string, std::string> args{};
    try {
        args = HttpParser::define_args_map(this->get_request_target());
        // args = this->get_args_url();
    }
    catch (HttpException::InvalidArguments& ec) {
        Logger::Error(__LINE__, __FILE__, ec.what());
        HttpClientErrorCreator<Send>::create_bad_request_400(std::forward<Send>(this->get_send()), this->get_request_version())->send_response();
        return;
    }

    try {
        // User user{};
        // user.delete_user();
        // TODO: удалить данные из БД
    }
    catch (std::out_of_range& ec) {
        return HttpClientErrorCreator<Send>
        ::create_bad_request_400(std::move(this->get_send()), this->get_request_version())->send_response();
    }

    return HttpSuccessCreator<Send>::create_ok_200(std::move(this->get_send()), this->get_request_version())->send_response();
}

#endif //SERVER_V0_1_USERMANAGER_HPP
