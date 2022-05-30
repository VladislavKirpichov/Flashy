//
// Created by vladislav on 20.05.22.
//

#ifndef SERVER_V0_1_HTTPCLIENTERRORS_HPP
#define SERVER_V0_1_HTTPCLIENTERRORS_HPP

#include <string>
#include <boost/beast.hpp>
#include <boost/beast/http.hpp>
#include "IHttpResponse.hpp"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>

template<typename Send>
class BadRequest400 : public IHttpResponse<http::string_body, Send> {
public:
    using IHttpResponse<http::string_body, Send>::IHttpResponse;
    void send_response() noexcept final {
        std::string_view error {"Bad Request 400\n"};
        http::response<http::string_body> res{http::status::bad_request, this->get_response_version()};

        res.body() = error;
        this->set_response_filds(res);

        return this->get_send()(std::move(res));
    }
};

template<typename Send>
class Unauthorized401 : public IHttpResponse<http::string_body, Send> {
public:
    using IHttpResponse<http::string_body, Send>::IHttpResponse;
    void send_response() noexcept final {
        std::string_view error {"Unauthorized 401\n"};
        http::response<http::string_body> res{http::status::unauthorized, this->get_response_version()};

        res.body() = error;
        this->set_response_filds(res);

        return this->get_send()(std::move(res));
    }
};

template<typename Send>
class Forbidden403 : public IHttpResponse<http::string_body, Send> {
public:
    using IHttpResponse<http::string_body, Send>::IHttpResponse;
    void send_response() noexcept final {
        std::string_view error {"Forbidden 403\n"};
        http::response<http::string_body> res{http::status::forbidden, this->get_response_version()};

        res.body() = error;
        this->set_response_filds(res);

        return this->get_send()(std::move(res));
    }
};

template<typename Send>
class NotFound404 : public IHttpResponse<http::string_body, Send> {
public:
    using IHttpResponse<http::string_body, Send>::IHttpResponse;
    void send_response() noexcept final {
        std::string_view error {"Not Found 404\n"};
        http::response<http::string_body> res{http::status::not_found, this->get_response_version()};

        res.body() = error;
        this->set_response_filds(res);

        return this->get_send()(std::move(res));
    }
};

template<typename Send>
class MethodNotAllowerd405 : public IHttpResponse<http::string_body, Send> {
public:
    using IHttpResponse<http::string_body, Send>::IHttpResponse;
    void send_response() noexcept final {
        std::string_view error {"Method Not Allowerd 405\n"};
        http::response<http::string_body> res{http::status::method_not_allowed, this->get_response_version()};

        res.body() = error;
        this->set_response_filds(res);

        return this->get_send()(std::move(res));
    }
};

template<typename Send>
class RequestTimeOut408 : public IHttpResponse<http::string_body, Send> {
public:
    using IHttpResponse<http::string_body, Send>::IHttpResponse;
    void send_response() noexcept final {
        std::string_view error {"Request Time Out 408\n"};
        http::response<http::string_body> res{http::status::request_timeout, this->get_response_version()};

        res.body() = error;
        this->set_response_filds(res);

        return this->get_send()(std::move(res));
    }
};

template<typename Send>
class UnsupportedMediaType415 : public IHttpResponse<http::string_body, Send> {
public:
    using IHttpResponse<http::string_body, Send>::IHttpResponse;
    void send_response() noexcept final {
        std::string_view error {"Request Time Out 408\n"};
        http::response<http::string_body> res{http::status::unsupported_media_type, this->get_response_version()};

        res.body() = error;
        this->set_response_filds(res);

        return this->get_send()(std::move(res));
    }
};


#endif //SERVER_V0_1_HTTPCLIENTERRORS_HPP
