//
// Created by vladislav on 22.05.22.
//

#ifndef SERVER_V0_1_HTTPSERVERERRORS_HPP
#define SERVER_V0_1_HTTPSERVERERRORS_HPP

#include "IHttpResponse.hpp"

template <typename Send>
class InternalServerError500 : public IHttpResponse<http::string_body, Send> {
public:
    using IHttpResponse<http::string_body, Send>::IHttpResponse;
    void send_response() noexcept final {
        std::string_view error {"Internal src Error 500\n"};
        http::response<http::string_body> res{http::status::internal_server_error, this->get_response_version()};

        res.body() = error;
        this->set_response_filds(res);

        return this->get_send()(std::move(res));
    }
};

// Can not be used with GET and HEAD!!!
template <typename Send>
class NotImplemented501 : public IHttpResponse<http::string_body, Send> {
public:
    using IHttpResponse<http::string_body, Send>::IHttpResponse;
    void send_response() noexcept final {
        std::string_view error {"Not Implemented 501\n"};
        http::response<http::string_body> res{http::status::not_implemented, this->get_response_version()};

        res.body() = error;
        this->set_response_filds(res);

        return this->get_send()(std::move(res));
    }
};

template <typename Send>
class ServiceUnavailable503 : public IHttpResponse<http::string_body, Send> {
public:
    using IHttpResponse<http::string_body, Send>::IHttpResponse;
    void send_response() noexcept final {
        std::string_view error {"Service Unavailable 503\n"};
        http::response<http::string_body> res{http::status::service_unavailable, this->get_response_version()};

        res.body() = error;
        this->set_response_filds(res);

        return this->get_send()(std::move(res));
    }
};

#endif //SERVER_V0_1_HTTPSERVERERRORS_HPP
