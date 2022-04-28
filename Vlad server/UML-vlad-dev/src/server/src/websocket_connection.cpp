//
// Created by vladislav on 28.04.22.
//

#include "websocket_connection.h"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio.hpp>
#include <iostream>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket;
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using error_code = boost::system::error_code;

websocket_connection::websocket_connection(tcp::socket&& socket) : _ws(std::move(socket)) {

}

websocket_connection::~websocket_connection() {

}

void websocket_connection::run(http::request<http::dynamic_body>&& req) {
    // Add coroutine here!

    _ws.async_accept(req, [self{shared_from_this()}](error_code ec){
        self->on_accept(ec);
    });
}

void websocket_connection::send(std::shared_ptr<const std::string> &ss) {

}

void websocket_connection::on_accept(error_code ec) {
    _ws.async_read(_buffer, [self{shared_from_this()}](error_code ec, size_t bytes_transferred){
//        boost::ignore_unused(bytes_transferred);
        self->on_read(ec, bytes_transferred);
    });
}

void websocket_connection::on_read(boost::system::error_code ec, size_t bytes_transferred) {
    if (ec == websocket::error::closed)
        return;

    // echo message
    _ws.text(_ws.got_text());

    _ws.async_write(_buffer.data(), [self{shared_from_this()}](error_code ec, size_t bytes_transferred){
        self->_buffer.consume(self->_buffer.size());
        self->on_accept(ec);
    });
}
