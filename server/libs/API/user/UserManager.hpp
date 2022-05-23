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
#include "DB.h"


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
}


/*
 * The GET method requests a representation of the specified resource.
 * Requests using GET should only retrieve data and should have no other effect.
*/


template<typename Body, typename Allocator, typename Send>
class GetUserManager : public IUserManager<Body, Allocator, Send> {
public:
    using IUserManager<Body, Allocator, Send>::IUserManager;
    void handle_request() final;

protected:
    std::vector<std::tuple<std::string, std::string>> get_args_url();
    void set_flags(http::response<http::string_body>&) override;
};

template<typename Body, typename Allocator, typename Send>
void GetUserManager<Body, Allocator, Send>::set_flags(http::response<http::string_body>& response) {
    response.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    response.set(http::field::content_type, "text/json");
    response.keep_alive(this->get_request_keep_alive());
}

template<typename Body, typename Allocator, typename Send>
std::vector<std::tuple<std::string, std::string>> GetUserManager<Body, Allocator, Send>::get_args_url() {
    std::vector<std::tuple<std::string, std::string>> args{};
    args = HttpParser::define_args(this->get_request_target());
    return args;
}

template<typename Body, typename Allocator, typename Send>
void GetUserManager<Body, Allocator, Send>::handle_request() {
    http::response<http::string_body> response{ http::status::ok, this->get_request_version()};
    std::vector<std::tuple<std::string, std::string>> args{};

    // Try to get args from url
    try {
        args = this->get_args_url();
    }
    catch (HttpException::InvalidArguments& ec) {
        Logger::Error(__LINE__, __FILE__, ec.what());
        HttpClientErrorCreator<Send>::create_bad_request_400(std::forward<Send>(this->get_send()), this->get_request_version())->send_response();
        return;
    }

    this->set_flags(response);

    // I - поставится вместо ?, 3 - кол-во столбцов
    // 3306
    // TODO: исправить работу БД
    // на данный момень сервер падает здесь
//    try {
//        DB *db = new DB("LAPTOP-9KQ1QFS1.local", "3306", "vladislav", "9192435969v", "Flashy");
//        std::vector<std::vector<std::string>> MyData{};
//        MyData = db->Get("SELECT FROM users WHERE id=?", {"I:4"}, 5);
//        db->Close();
//    }
//    catch (...) {
//        Logger::Critical(__LINE__, __FILE__, "DB error");
//        HttpServerErrorCreator<Send>::create_internal_server_error_500(std::move(this->get_send()), this->get_request_version())->send_response();
//        throw std::exception();
//    }

    // Find user by id
    // TODO: взять информацию о пользователе из БД
    // this->find_user_in_db();

    try {
        if (std::get<0>(args[0]) == "id" && std::get<1>(args[0]) == "1")
            response.body() = JsonSerializer::serialize(USER_1);

        else if (std::get<0>(args[0]) == "id" && std::get<1>(args[0]) == "2")
            response.body() = JsonSerializer::serialize(USER_2);

        else if (std::get<0>(args[0]) == "id" && std::get<1>(args[0]) == "3")
            response.body() = JsonSerializer::serialize(USER_3);

        else if (std::get<0>(args[0]) == "id" && std::get<1>(args[0]) == "4")
            response.body() = JsonSerializer::serialize(USER_4);

        else
            throw APIException::UserException("user not found");
    }
    catch (JsonException::JsonException& ec) {
        // TODO: написать обработчик
        return;
    }
    catch (APIException::UserException& ec) {
        // TODO: написат обработчик
        return;
    }

    response.content_length(response.body().size());

    return this->get_send()(std::move(response));
}


/*
 * The PUT method requests that the enclosed entity be stored under the supplied URI.
 * If the URI refers to an already existing resource, it is modified;
 * if the URI does not point to an existing resource, then the server
 * can create the resource with that URI.
*/


template<typename Body, typename Allocator, typename Send>
class PutUserManager : public IUserManager<Body, Allocator, Send> {
public:
    using IUserManager<Body, Allocator, Send>::IUserManager;
    void handle_request() final;

protected:
    std::vector<std::vector<std::string>> get_request_data_in_vector();
};

template<typename Body, typename Allocator, typename Send>
void PutUserManager<Body, Allocator, Send>::handle_request() {
    std::vector<std::vector<std::string>> request_data = this->get_request_data_in_vector();

    // TODO: Положить данные в базу
    //  Ссылка с описанием методов: https://www.boost.org/doc/libs/1_67_0/boost/beast/http/verb.hpp

    HttpSuccessCreator<Send>::create_ok_200(std::move(this->get_send()), this->get_request_version())->send_response();
}

template<typename Body, typename Allocator, typename Send>
std::vector<std::vector<std::string>> PutUserManager<Body, Allocator, Send>::get_request_data_in_vector() {
    std::string data = this->get_request_body_data();
    std::vector<std::vector<std::string>> vector_data = JsonSerializer::deserialize(data);
    return vector_data;
}

//template<typename Body, typename Allocator, typename Send>
//void PutUserManager<Body, Allocator, Send>::send_failure() {
//    http::response<http::string_body>
//}


/*
 * The POST method requests that the server accept the entity enclosed
 * in the request as a new subordinate of the web resource identified by the URI.
 *
 * The data POSTed might be, for example, an annotation for existing
 * resources; a message for a bulletin board, newsgroup, mailing list,
 * or comment thread; a block of data that is the result of submitting
 * a web form to a data-handling process; or an item to add to a database
*/


template<typename Body, typename Allocator, typename Send>
class PostUserManager : public IUserManager<Body, Allocator, Send> {
public:
    using IUserManager<Body, Allocator, Send>::IManager;
    void handle_request() final;
};

template<typename Body, typename Allocator, typename Send>
void PostUserManager<Body, Allocator, Send>::handle_request() {
    std::vector<std::vector<std::string>> request_data = this->get_request_data();

    // TODO: Положить данные в базу
    //  Ссылка с описанием методов: https://www.boost.org/doc/libs/1_67_0/boost/beast/http/verb.hpp

    HttpSuccessCreator<Send>::create_ok_200(std::move(this->get_send()), this->get_request_version())->send_response();
}

#endif //SERVER_V0_1_USERMANAGER_HPP
