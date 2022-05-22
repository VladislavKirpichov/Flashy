//
// Created by vladislav on 20.05.22.
//

#ifndef SERVER_V0_1_HTTPCLIENTERRORS_HPP
#define SERVER_V0_1_HTTPCLIENTERRORS_HPP

#include <string>
#include <boost/beast.hpp>
#include <boost/beast/http.hpp>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>

// Interface for all Http Errors Classes
template<typename Send>
class HttpError {
public:
    explicit HttpError(Send&& send, unsigned response_version = 11)
        : _response_version(response_version),
          _send(std::move(send)) {}

    virtual void send_response() noexcept = 0;

protected:
    void set_response_filds(http::response<http::string_body>& res);

    unsigned int _response_version;
    Send _send;
};

template<typename Send>
void HttpError<Send>::set_response_filds(http::response<http::string_body>& res) {
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/text");
    res.content_length(res.body().size());
}

template<typename Send>
class BadRequest400 : public HttpError<Send> {
public:
    explicit BadRequest400(Send&& send, unsigned response_version) : HttpError<Send>(std::move(send), response_version) {}
    void send_response() noexcept final {
        std::string_view error {"Bad Request 400\n"};
        http::response<http::string_body> res{http::status::bad_request, this->_response_version};

        res.body() = error;
        this->set_response_filds(res);

        return this->_send(std::move(res));
    }
};

template<typename Send>
class Unauthorized401 : public HttpError<Send> {
public:
    explicit Unauthorized401(Send&& send, unsigned response_version) : HttpError<Send>(std::move(send), response_version) {}
    void send_response() noexcept final {
        std::string_view error {"Unauthorized 401\n"};
        http::response<http::string_body> res{http::status::unauthorized, this->_response_version};

        res.body() = error;
        this->set_response_filds(res);

        return this->_send(std::move(res));
    }
};

template<typename Send>
class Forbidden403 : public HttpError<Send> {
public:
    explicit Forbidden403(Send&& send, unsigned response_version) : HttpError<Send>(std::move(send), response_version) {}
    void send_response() noexcept final {
        std::string_view error {"Forbidden 403\n"};
        http::response<http::string_body> res{http::status::forbidden, this->_response_version};

        res.body() = error;
        this->set_response_filds(res);

        return this->_send(std::move(res));
    }
};

template<typename Send>
class NotFound404 : public HttpError<Send> {
public:
    explicit NotFound404(Send&& send, unsigned response_version) : HttpError<Send>(std::move(send), response_version) {}
    void send_response() noexcept final {
        std::string_view error {"Not Found 404\n"};
        http::response<http::string_body> res{http::status::not_found, this->_response_version};

        res.body() = error;
        this->set_response_filds(res);

        return this->_send(std::move(res));
    }
};

template<typename Send>
class MethodNotAllowerd405 : public HttpError<Send> {
public:
    explicit MethodNotAllowerd405(Send&& send, unsigned response_version) : HttpError<Send>(std::move(send), response_version) {}
    void send_response() noexcept final {
        std::string_view error {"Method Not Allowerd 405\n"};
        http::response<http::string_body> res{http::status::method_not_allowed, this->_response_version};

        res.body() = error;
        this->set_response_filds(res);

        return this->_send(std::move(res));
    }
};

template<typename Send>
class RequestTimeOut408 : public HttpError<Send> {
public:
    explicit RequestTimeOut408(Send&& send, unsigned response_version) : HttpError<Send>(std::move(send), response_version) {}
    void send_response() noexcept final {
        std::string_view error {"Request Time Out 408\n"};
        http::response<http::string_body> res{http::status::request_timeout, this->_response_version};

        res.body() = error;
        this->set_response_filds(res);

        return this->_send(std::move(res));
    }
};

template<typename Send>
class UnsupportedMediaType415 : public HttpError<Send> {
public:
    explicit UnsupportedMediaType415(Send&& send, unsigned response_version) : HttpError<Send>(std::move(send), response_version) {}
    void send_response() noexcept final {
        std::string_view error {"Request Time Out 408\n"};
        http::response<http::string_body> res{http::status::unsupported_media_type, this->_response_version};

        res.body() = error;
        this->set_response_filds(res);

        return this->_send(std::move(res));
    }
};


#endif //SERVER_V0_1_HTTPCLIENTERRORS_HPP
