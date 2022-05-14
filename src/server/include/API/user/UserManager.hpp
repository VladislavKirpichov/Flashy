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


namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using error_code = boost::system::error_code;


template<typename Body, typename Allocator, typename Send>
class UserManager : public std::enable_shared_from_this<UserManager<Body, Allocator, Send>> {
public:
    UserManager(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send);

    virtual void handle_request() = 0;

protected:
    virtual http::file_body::value_type create_body(const char* file_path) = 0;
    // virtual http::file_body::value_type create_responce() = 0;

    Send _send;
    http::request<Body, http::basic_fields<Allocator>> _request;
};

template<typename Body, typename Allocator, typename Send>
UserManager<Body, Allocator, Send>::UserManager(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send)
        : _request(std::move(req)),
          _send(std::forward<Send>(send)) {}

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

    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/json");
    res.body() = "test";
    res.content_length(res.body().size());
    res.keep_alive(this->_request.keep_alive());

    return this->_send(std::move(res));
}

template<typename Body, typename Allocator, typename Send>
http::file_body::value_type GetUserManager<Body, Allocator, Send>::create_body(const char* file_path) {

}

#endif //SERVER_V0_1_USERMANAGER_HPP