//
// Created by vladislav on 22.04.22.
//

#include "Listener.h"

#include <iostream>

#include <boost/beast/core.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>

#include "API_Gateway.hpp"
#include "../../Logger/Logger.hpp"
#include "Exceptions.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using error_code = boost::system::error_code;


Listener::Listener(net::io_context &ioc, boost::asio::ip::tcp::endpoint&& endpoint)
: _ioc(ioc), _acceptor(net::make_strand(ioc)), _socket(ioc) {
    // Initialize Listener
    error_code ec;
    _acceptor.open(endpoint.protocol(), ec);
    if (ec)
        throw (ServerException::ListenerException(ec));

    _acceptor.set_option(net::socket_base::reuse_address(true), ec);
    if (ec)
        throw (ServerException::ListenerException(ec));

    _acceptor.bind(endpoint, ec);
    if (ec)
        throw (ServerException::ListenerException(ec));

    _acceptor.listen(net::socket_base::max_listen_connections, ec);
    if (ec)
        throw (ServerException::ListenerException(ec));
}

Listener::~Listener() {
    _acceptor.close();
    Logger::Info(__LINE__, __FILE__, "destroyed connection");
}

// Start accepting connection
void Listener::async_accept() {
    try {
        // delayed until it gets a new connection
        // socket holds new connection
        // shared_from_this extends lifetime of shared_ptr
        _acceptor.async_accept(_socket, [self{shared_from_this()}](error_code ec){
            if (ec == http::error::end_of_stream)
                return;

            if (ec) {
                Logger::Error(__LINE__, __FILE__, "error in async_accept: %s", ec.message().data());
                return;
            }

            std::cout << "Connection accepted" << "\n";

            self->on_accept(ec);
        });
    }

    catch (error_code& ec) {
        Logger::Critical(__LINE__, __FILE__, "catch error in async_error: %s", ec.message().data());
    }
}

void Listener::on_accept(error_code &ec) {
    if (ec) {
        Logger::Error(__LINE__, __FILE__, "error in on_accept: %s", ec.message().data());
        return;
    }

    std::make_shared<API_Gateway>(std::move(_ioc), std::move(_socket))->read_request();

    // Allows to create an event loop
    async_accept();
}