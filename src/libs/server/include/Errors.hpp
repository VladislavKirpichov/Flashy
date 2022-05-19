//
// Created by vladislav on 19.05.22.
//

#ifndef SERVER_V0_1_ERRORS_HPP
#define SERVER_V0_1_ERRORS_HPP

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

namespace Errors {
    // Interface for all error classes
    template<typename Body, typename Allocator, typename Send>
    class ErrorResponse {
    public:
        ErrorResponse(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send)
                : _request(std::move(req)),
                  _send(std::forward<Send>(send)) {}

        virtual void send_response() = 0;

        Send _send;
        http::request<Body, http::basic_fields<Allocator>> _request;
    };

    template<typename Body, typename Allocator, typename Send>
    class BadRequest_400 : public ErrorResponse<Body, Allocator, Send> {
    public:
        BadRequest_400(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send)
                : ErrorResponse<Body, Allocator, Send>(std::move(req), std::forward<Send>(send)) {}

        void send_response() final {
            http::response<http::string_body> res{ http::status::bad_request, this->_request.version()};
            res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
            res.body() = "error 400 bad request";
            res.keep_alive(this->_request.keep_alive());

            return this->_send(std::move(res));
        }
    };
}


template<typename Body, typename Allocator, typename Send>
class ErrorCreator {
public:
    static std::shared_ptr<Errors::BadRequest_400<Body, Allocator, Send>> create_BadRequest(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send);
};

template<typename Body, typename Allocator, typename Send>
std::shared_ptr<Errors::BadRequest_400<Body, Allocator, Send>>
ErrorCreator<Body, Allocator, Send>::create_BadRequest(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send) {
    return std::make_shared<Errors::BadRequest_400<Body, Allocator, Send>>(std::move(req), std::forward<Send>(send));
}

#endif //SERVER_V0_1_ERRORS_HPP
