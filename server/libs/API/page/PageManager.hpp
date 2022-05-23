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

#include "IManager.hpp"
#include "JsonSerializer.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using error_code = boost::system::error_code;


template<typename Body, typename Allocator, typename Send>
class IPageManager : public IManager<Body, Allocator, Send> {
public:
    using IManager<Body, Allocator, Send>::IManager;
    virtual void handle_request() = 0;
};


// GET


template<typename Body, typename Allocator, typename Send>
class GetPageManager : public IPageManager<Body, Allocator, Send> {
public:
    using IPageManager<Body, Allocator, Send>::IPageManager;
    void handle_request() final;
};

template<typename Body, typename Allocator, typename Send>
void GetPageManager<Body, Allocator, Send>::handle_request() {
    std::vector<std::vector<std::string>> data {
            {"headline", "Test Page"},
            {"page_id", "1"},
            {"tests_id", "1", "2", "3", "4"}
    };

    http::file_body::value_type body;

    http::response<http::string_body> res{http::status::ok, this->get_request_version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/json");
    res.body() = JsonSerializer::serialize(data);
    res.content_length(res.body().size());
    res.keep_alive(this->get_request_keep_alive());

    return this->get_send()(std::move(res));
}


// PUT


template<typename Body, typename Allocator, typename Send>
class PutPageManager : public IPageManager<Body, Allocator, Send> {
public:
    using IPageManager<Body, Allocator, Send>::IPageManager;
    void handle_request() final;
};

template<typename Body, typename Allocator, typename Send>
void PutPageManager<Body, Allocator, Send>::handle_request() {
    std::vector<std::vector<std::string>> data {
            {"headline", "Test Page"},
            {"page_id", "1"},
            {"tests_id", "1", "2", "3", "4"}
    };

    http::file_body::value_type body;

    http::response<http::string_body> res{http::status::ok, this->get_request_version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/json");
    res.body() = JsonSerializer::serialize(data);
    res.content_length(res.body().size());
    res.keep_alive(this->get_request_keep_alive());

    return this->get_send()(std::move(res));
}

// POST


template<typename Body, typename Allocator, typename Send>
class PostPageManager : public IPageManager<Body, Allocator, Send> {
public:
    using IPageManager<Body, Allocator, Send>::IPageManager;
    void handle_request() final;
};

template<typename Body, typename Allocator, typename Send>
void PostPageManager<Body, Allocator, Send>::handle_request() {
    std::vector<std::vector<std::string>> data {
            {"headline", "Test Page"},
            {"page_id", "1"},
            {"tests_id", "1", "2", "3", "4"}
    };

    http::file_body::value_type body;

    http::response<http::string_body> res{http::status::ok, this->get_request_version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/json");
    res.body() = JsonSerializer::serialize(data);
    res.content_length(res.body().size());
    res.keep_alive(this->get_request_keep_alive());

    return this->get_send()(std::move(res));
}


// DELETE


template<typename Body, typename Allocator, typename Send>
class DeletePageManager : public IPageManager<Body, Allocator, Send> {
public:
    using IPageManager<Body, Allocator, Send>::IPageManager;
    void handle_request() final;
};

template<typename Body, typename Allocator, typename Send>
void DeletePageManager<Body, Allocator, Send>::handle_request() {
    std::vector<std::vector<std::string>> data {
            {"headline", "Test Page"},
            {"page_id", "1"},
            {"tests_id", "1", "2", "3", "4"}
    };

    http::file_body::value_type body;

    http::response<http::string_body> res{http::status::ok, this->get_request_version()};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/json");
    res.body() = JsonSerializer::serialize(data);
    res.content_length(res.body().size());
    res.keep_alive(this->get_request_keep_alive());

    return this->get_send()(std::move(res));
}

#endif //SERVER_V0_1_PAGEMANAGER_HPP
