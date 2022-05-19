//
// Created by vladislav on 06.05.22.
//

#ifndef SERVER_V0_1_PAGEMANAGER_HPP
#define SERVER_V0_1_PAGEMANAGER_HPP

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

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using error_code = boost::system::error_code;


template<typename Body, typename Allocator, typename Send>
class PageManager : public std::enable_shared_from_this<PageManager<Body, Allocator, Send>> {
public:
    PageManager(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send);

    virtual void handle_request() = 0;

protected:

    virtual http::file_body::value_type create_body(const char* file_path) = 0;
    // virtual http::file_body::value_type create_responce() = 0;

    Send _send;
    http::request<Body, http::basic_fields<Allocator>> _request;
};

template<typename Body, typename Allocator, typename Send>
PageManager<Body, Allocator, Send>::PageManager(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send)
        : _request(std::move(req)),
          _send(std::forward<Send>(send)) {}

template<typename Body, typename Allocator, typename Send>
class GetPageManager : public PageManager<Body, Allocator, Send> {
public:
    GetPageManager(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send)
            : PageManager<Body, Allocator, Send>(std::move(req), std::forward<Send>(send)) {}

    void handle_request() final;

private:
    http::file_body::value_type create_body(const char* file_path) final;
    // http::file_body::value_type create_responce() final;
};

// GET_PageManager, POST_PageManager, PUT_PageManager ...

template<typename Body, typename Allocator, typename Send>
void GetPageManager<Body, Allocator, Send>::handle_request() {
    std::vector<std::vector<std::string>> data {
            {"headline", "Test Page"},
            {"page_id", "1"},
            {"tests_id", "1", "2", "3", "4"}
    };

    http::file_body::value_type body;

    http::response<http::string_body> res{http::status::ok, this->_request.version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/json");
    res.body() = JsonSerializer::serialize(data);
    res.content_length(res.body().size());
    res.keep_alive(this->_request.keep_alive());

    return this->_send(std::move(res));
}

template<typename Body, typename Allocator, typename Send>
http::file_body::value_type GetPageManager<Body, Allocator, Send>::create_body(const char* file_path) {
    http::file_body::value_type body;
    error_code ec_http_body;
    body.open(file_path, beast::file_mode::scan, ec_http_body);

    if (ec_http_body) {
        // Logger::Error(__LINE__, __FILE__, "error in body.open()");
    }
    return body;
}

#endif //SERVER_V0_1_PAGEMANAGER_HPP
