//
// Created by vladislav on 25.04.22.
//

#include "http_connection.h"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio.hpp>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>
#include <functional>

#include "websocket_connection.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using error_code = boost::system::error_code;


http_connection::http_connection(boost::asio::ip::tcp::socket socket) : _socket(std::move(socket)) {}

void http_connection::run() {
    read_request();
    check_deadline();
}

void http_connection::read_request() {
    http::async_read(_socket, _buffer, _request, [self{shared_from_this()}](error_code ec, std::size_t bytes_transferred){
        boost::ignore_unused(bytes_transferred);

        // handle connection close here!!!
        if (ec) {
            self->_socket.shutdown(tcp::socket::shutdown_send, ec);
            return;
        }

        self->process_request(ec, bytes_transferred);
        self->read_request();
    });
}

void http_connection::process_request(error_code& ec, std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    if (beast::websocket::is_upgrade(_request)){
        // Create a WebSocket session by transferring the socket
        std::make_shared<websocket_connection>(std::move(_socket))->run(std::move(_request));
        return;
    }

    if (ec) std::cout << "error in http_connection::process_request: " << ec.message() << "\n";

    _response.version(_request.version());
    _response.keep_alive(false);

    switch (_request.method()) {
        case http::verb::get:
            _response.result(http::status::ok);
            _response.set(http::field::server, "Beast Server");
            create_response();
            break;

        default:
            // Return response indicating error if we do not recognize the request method
            _response.result(http::status::bad_request);
            _response.set(http::field::content_type, "text/plain");

            beast::ostream(_response.body())
                << "Invalid request method"
                << std::string(_request.method_string())
                << "\n";
            break;
    }
}

void http_connection::create_response() {
    if (_request.target() == "/test") {
        _response.set(http::field::content_type, "text/html");
        beast::ostream(_response.body())
            <<  "<html>\n"
            <<  "<head><title>Request count</title></head>\n"
            <<  "<body>\n"
            <<  "<h1>Test Response</h1>\n"
            <<  "<p>Hello world from my beast server!</p>\n"
            <<  "</body>\n"
            <<  "</html>\n";
    }

    else {
        _response.set(http::field::content_type, "test/html");
        beast::ostream(_response.body())
            <<  "<html>\n"
            <<  "<head><title>Request count</title></head>\n"
            <<  "<body>\n"
            <<  "<h1>Bad Page(</h1>\n"
            <<  "<p>Go to /test to see valid responce</p>\n"
            <<  "</body>\n"
            <<  "</html>\n";
    }
}

void http_connection::check_deadline() {
    _deadline.async_wait([self{shared_from_this()}](error_code const& ec){
       if (!ec)
           self->_socket.close();
    });
}