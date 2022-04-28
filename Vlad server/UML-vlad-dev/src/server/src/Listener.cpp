//
// Created by vladislav on 22.04.22.
//

#include "Listener.h"

#include <iostream>

#include <boost/beast/core.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>

#include "http_connection.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using error_code = boost::system::error_code;


Listener::Listener(net::io_context &ioc, const std::string& ip_address, unsigned short port)
: _ioc(ioc), _acceptor(ioc, {net::ip::make_address(ip_address), port}), _socket(ioc) {}

Listener::~Listener() {
    std::cout << "destroyed connection" << '\n';
}

// Start accepting connection
void Listener::async_accept() {
    try {
        // delayed until it gets a new connection
        // socket holds new connection
        // shared_from_this extends lifetime of shared_ptr
        _acceptor.async_accept(_socket, [self{shared_from_this()}](error_code ec){
            if (ec) std::cout << "Listener exception async_accept: " << ec.message() << "\n";
            std::cout << "Connection accepted" << "\n";

            self->on_accept(ec);
            self->async_accept();
        });
    }

    catch (error_code& ec) {
        std::cout << "Listener exception: " << ec.message() << std::endl;
    }
}

void Listener::on_accept(error_code &ec) {
    if (ec)
        std::cout << "Listener accept error: " << ec.message() << std::endl;

    std::make_shared<http_connection>(std::move(_socket))->run();
}