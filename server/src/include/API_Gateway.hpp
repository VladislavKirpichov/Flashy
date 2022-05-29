//
// Created by vladislav on 25.04.22.
//

#ifndef SERVER_V0_1_API_GATEWAY_HPP
#define SERVER_V0_1_API_GATEWAY_HPP

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/version.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio/detail/reactive_socket_service_base.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/config.hpp>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>
#include <functional>
#include <tuple>

#include "RequestHandler.hpp"
#include "../../Logger/Logger.hpp"
#include "Exceptions.h"
#include "HttpClientErrorCreator.hpp"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using error_code = boost::system::error_code;


/*
 *  Interface for classes that implement the
 *  logic of working with different http headers
 *
 *  The inherited classes process the request, access different APIs that generate a http response
*/
class API_Gateway : public std::enable_shared_from_this<API_Gateway> {
public:
    API_Gateway(boost::asio::io_context&& ioc, boost::asio::ip::tcp::socket&& socket);
    void read_request();

private:
    // functor for sending entities
    class Send {
    public:
        API_Gateway& _self;
        explicit Send(API_Gateway& self):
            _self(self) {}

        // Called by the RequestHandler to send a response.
        // see: https://www.boost.org/doc/libs/develop/libs/beast/doc/html/beast/ref/boost__beast__http__message.html
        template<bool isRequest, typename Body, typename Fields>
        void operator()(http::message<isRequest, Body, Fields>&& msg) const {
            // Creates copy of msg
            auto sp = std::make_shared<http::message<isRequest, Body, Fields>>(std::move(msg));
            _self._response = sp;

            Logger::Info(__LINE__, __FILE__, "sent response");

            http::async_write(_self._stream, *sp, [me{_self.shared_from_this()}](error_code ec, std::size_t bytes_transferred) {
                boost::ignore_unused(bytes_transferred);

                if (ec) {
                    Logger::Error(__LINE__, __FILE__, "http::async_write: %s", ec.message().data());
                    return;
                }

                // We're done with the response so delete it
                me->_response = nullptr;
            });
        }
    };

    void handle_request();

    // Closes socket to cancel any outstanding operation
    void close_connection();

    boost::beast::tcp_stream _stream;
    boost::asio::ip::tcp::resolver _resolver;
    boost::beast::flat_buffer _buffer{8192};

    // A dynamic message body represented by a multi_buffer.
    http::request<http::dynamic_body> _request;
    std::shared_ptr<void> _response;

    // Send functor
    Send send{*this};
};

API_Gateway::API_Gateway(boost::asio::io_context &&ioc, tcp::socket &&socket)
    : _resolver(ioc),
      _stream(std::move(socket)) {}

void API_Gateway::read_request() {
    Logger::Info(__LINE__, __FILE__, "handle_request");

    http::async_read(_stream, _buffer, _request, [self{shared_from_this()}](error_code ec, std::size_t bytes_transferred) {
        if (ec == http::error::end_of_stream)
            return;

        if (ec) {
            self->close_connection();
            std::cout << ec << '\n';
            std::cout << ec.message() << '\n';
            throw ServerException::APIGatewayException(ec);
        }

        self->handle_request();
    });
}

void API_Gateway::handle_request() {
    try {
        if (_request.method() == http::verb::get) {
            std::make_unique<GetHandler<http::dynamic_body, std::allocator<char>, Send>>(std::move(_request), std::forward<Send>(send))->process_request();
        }
        else if (_request.method() == http::verb::put) {
            std::make_unique<PutHandler<http::dynamic_body, std::allocator<char>, Send>>(std::move(_request), std::forward<Send>(send))->process_request();
        }
        else if (_request.method() == http::verb::post) {
            std::make_unique<PostHandler<http::dynamic_body, std::allocator<char>, Send>>(std::move(_request), std::forward<Send>(send))->process_request();
        }
        else if (_request.method() == http::verb::delete_) {
            std::make_unique<DeleteHandler<http::dynamic_body, std::allocator<char>, Send>>(std::move(_request), std::forward<Send>(send))->process_request();
        }
        else {
            HttpClientErrorCreator<Send>::create_method_not_allowed_405(std::forward<Send>(send), this->_request.version())->send_response();
        }
    }
    catch (HttpException::HttpException& ec) {
        Logger::Info(__LINE__, __FILE__, ec.what());
    }
    catch (ServerException::ServerException& ec) {
        Logger::Error(__LINE__, __FILE__, ec.what());
        throw ServerException::APIGatewayException(ec);
    }
}

void API_Gateway::close_connection() {
    error_code ec;
    _stream.socket().close(ec);
}


#endif //SERVER_V0_1_API_GATEWAY_HPP
