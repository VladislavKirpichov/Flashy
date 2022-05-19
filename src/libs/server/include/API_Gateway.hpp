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
#include "Logger.hpp"

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
    // functor for sending data
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

                // Read another request
                me->read_request();
            });
        }
    };

    void handle_request();

    // Closes socket to cancel any outstanding operation

    boost::beast::tcp_stream _stream;
    boost::asio::ip::tcp::resolver _resolver;
    boost::beast::flat_buffer _buffer{8192};

    // A dynamic message body represented by a multi_buffer.
    http::request<http::dynamic_body> _request;
    std::shared_ptr<void> _response;

    // Send functor
    Send send{*this};
};

API_Gateway::API_Gateway(boost::asio::io_context &&ioc, tcp::socket &&socket):
        _resolver(ioc), _stream(std::move(socket)) {}

void API_Gateway::read_request() {
    Logger::Info(__LINE__, __FILE__, "handle_request");

    http::async_read(_stream, _buffer, _request, [self{shared_from_this()}](error_code ec, std::size_t bytes_transferred){
        if (ec) {
            Logger::Error(__LINE__, __FILE__, "read_request: %s", ec.message().data());
            return;
            // return close_connection();
        }

        self->handle_request();
    });
}

void API_Gateway::handle_request() {
    if (_request.method() == http::verb::get) {
//        if (boost::starts_with(_request.target(), "/api/")) {
//            RequestHandler::GETHandler getHandler(std::move(_request), std::forward<Send>(send));
//            getHandler.process_request();   // expects rvalue
//        }
        RequestHandler::GETHandler getHandler(std::move(_request), std::forward<Send>(send));
        getHandler.process_request();   // expects rvalue
    }
}


#endif //SERVER_V0_1_API_GATEWAY_HPP
