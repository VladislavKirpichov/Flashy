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
#include "HttpSuccessCreator.hpp"
#include "HttpClientErrorCreator.hpp"
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


// TODO: Добавить классы POST, PUT, DELETE

template<typename Body, typename Allocator, typename Send>
class UserManager : public std::enable_shared_from_this<UserManager<Body, Allocator, Send>> {
public:
    UserManager(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send);

    virtual void handle_request() = 0;

    Send _send;

protected:
    std::string get_request_target();
    std::string get_request_data();
    unsigned int get_request_version();
    bool request_keep_alive() { return this->_request.keep_alive(); }

private:
    http::request<Body, http::basic_fields<Allocator>> _request;
};

template<typename Body, typename Allocator, typename Send>
UserManager<Body, Allocator, Send>::UserManager(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send)
        : _request(std::move(req)),
          _send(std::forward<Send>(send)) {}

template<typename Body, typename Allocator, typename Send>
std::string UserManager<Body, Allocator, Send>::get_request_target() {
    return this->_request.base().target().template to_string();
}

template<typename Body, typename Allocator, typename Send>
unsigned int UserManager<Body, Allocator, Send>::get_request_version() {
    return this->_request.version();
}

template<typename Body, typename Allocator, typename Send>
std::string UserManager<Body, Allocator, Send>::get_request_data() {
    return beast::buffers_to_string(this->_request.body().data());
}


// --------------- GET ---------------


template<typename Body, typename Allocator, typename Send>
class GetUserManager : public UserManager<Body, Allocator, Send> {
public:
    GetUserManager(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send)
            : UserManager<Body, Allocator, Send>(std::move(req), std::forward<Send>(send)) {}

    void handle_request() final;
};

template<typename Body, typename Allocator, typename Send>
void GetUserManager<Body, Allocator, Send>::handle_request() {

    http::response<http::string_body> res{ http::status::ok, this->get_request_version()};
    std::vector<std::tuple<std::string, std::string>> args{};

    // Try to get args from url
    try {
        args = HttpParser::define_args(this->get_request_target());
    }
    catch (HttpException::InvalidArguments& ec) {
        Logger::Error(__LINE__, __FILE__, ec.what());
        HttpClientErrorCreator<Send>::create_bad_request_400(std::forward<Send>(this->_send), this->get_request_version())->send_response();
        return;
    }

    // Set flags
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/json");
    res.keep_alive(this->request_keep_alive());

    // Find user by id
    // TODO: взять информацию о пользователе из БД
    if (std::get<0>(args[0]) == "id" && std::get<1>(args[0]) == "1")
        res.body() = JsonSerializer::serialize(USER_1);

    else if (std::get<0>(args[0]) == "id" && std::get<1>(args[0]) == "2")
        res.body() = JsonSerializer::serialize(USER_2);

    else if (std::get<0>(args[0]) == "id" && std::get<1>(args[0]) == "3")
        res.body() = JsonSerializer::serialize(USER_3);

    else if (std::get<0>(args[0]) == "id" && std::get<1>(args[0]) == "4")
        res.body() = JsonSerializer::serialize(USER_4);

    else
        throw APIException::UserException("user not found");

    res.content_length(res.body().size());

    return this->_send(std::move(res));
}


/*
 * The PUT method requests that the enclosed entity be stored under the supplied URI.
 * If the URI refers to an already existing resource, it is modified;
 * if the URI does not point to an existing resource, then the server
 * can create the resource with that URI.
*/


template<typename Body, typename Allocator, typename Send>
class PutUserManager : public UserManager<Body, Allocator, Send> {
public:
    PutUserManager(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send)
            : UserManager<Body, Allocator, Send>(std::move(req), std::forward<Send>(send)) {}

    void handle_request() final;

protected:
    std::vector<std::vector<std::string>> get_data_from_request();
};

template<typename Body, typename Allocator, typename Send>
void PutUserManager<Body, Allocator, Send>::handle_request() {
    std::vector<std::vector<std::string>> request_data = this->get_data_from_request();

    // TODO: Положить данные в базу
    //  Ссылка с описанием методов: https://www.boost.org/doc/libs/1_67_0/boost/beast/http/verb.hpp

    HttpSuccessCreator<Send>::create_ok_200(std::move(this->_send), this->get_request_version())->send_response();
}

template<typename Body, typename Allocator, typename Send>
std::vector<std::vector<std::string>> PutUserManager<Body, Allocator, Send>::get_data_from_request() {
    std::string data = this->get_request_data();
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
class PostUserManager : public UserManager<Body, Allocator, Send> {
public:
    PostUserManager(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send)
            : UserManager<Body, Allocator, Send>(std::move(req), std::forward<Send>(send)) {}

    void handle_request() final;
};

template<typename Body, typename Allocator, typename Send>
void PostUserManager<Body, Allocator, Send>::handle_request() {
    std::vector<std::vector<std::string>> request_data = this->get_request_data();

    // TODO: Положить данные в базу
    //  Ссылка с описанием методов: https://www.boost.org/doc/libs/1_67_0/boost/beast/http/verb.hpp

    HttpSuccessCreator<Send>::create_ok_200(std::move(this->_send), this->get_request_version())->send_response();
}

#endif //SERVER_V0_1_USERMANAGER_HPP
