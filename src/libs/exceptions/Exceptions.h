//
// Created by vladislav on 20.05.22.
//

#ifndef SERVER_V0_1_ERRORS_H
#define SERVER_V0_1_ERRORS_H

#include <stdexcept>
#include <boost/system/error_code.hpp>


// ---------- LAYER 3.1 | HTTP ----------


namespace HttpException {
    // Interface for all HTTP exceptions
    class HttpException : public std::runtime_error {
    public:
        HttpException() : std::runtime_error("Http Parser Exception") {}
        explicit HttpException(const char* msg) : std::runtime_error("Http Parser Exception: " + std::string(msg)) {}
        explicit HttpException(std::string& msg) : std::runtime_error("Http Parser Exception: " + msg) {}
        using std::runtime_error::runtime_error;
    };

    class NotDefinedType : public HttpException {
    public:
        using HttpException::HttpException;
        NotDefinedType() : HttpException("Not Defined Type") {}
    };

    class InvalidArguments : public HttpException {
    public:
        using HttpException::HttpException;
        InvalidArguments() : HttpException("Invalid Arguments") {}
    };

}   // namespace HttpException


// ---------- LAYER 3.2 | JSON ----------


namespace JsonException {
    // Interface for all JSON exceptions
    class JsonException : public std::runtime_error {
    public:
        JsonException() : std::runtime_error("Json Exception") {}
        explicit JsonException(const char* msg) : std::runtime_error(msg) {}
        explicit JsonException(std::string& msg) : std::runtime_error(msg) {}
        using std::runtime_error::runtime_error;
    };
}   // namespace JsonException


// ---------- LAYER 2 | API ----------


namespace APIException {
    typedef HttpException::HttpException HttpException;
    typedef JsonException::JsonException JsonException;

    // Interface for all API exceptions
    class APIException : public std::runtime_error {
    public:
        using std::runtime_error::runtime_error;

        APIException()
            : std::runtime_error("API Exception"),
              http_exception("\0"),
              json_exception("\0") {}

        explicit APIException(const char *msg)
                : std::runtime_error(msg),
                  http_exception("\0"),
                  json_exception("\0") {}

        explicit APIException(const std::string& msg)
                : std::runtime_error(msg),
                  http_exception("\0"),
                  json_exception("\0") {}

        APIException(const char *msg, const HttpException &http_exception, const JsonException& json_exception)
                : std::runtime_error(msg),
                  http_exception(http_exception.what()),
                  json_exception(json_exception.what()) {}

        APIException(const std::string& msg, const HttpException &http_exception, const JsonException& json_exception)
                : std::runtime_error(msg),
                  http_exception(http_exception.what()),
                  json_exception(json_exception.what()) {}

        APIException(APIException& api_exception)
            : std::runtime_error(api_exception.what()),
              http_exception("\0"),
              json_exception("\0") {}

        [[nodiscard]] const char *what() const noexcept {
            http_exception.what();
            json_exception.what();
            return "API Exception\n";
        }

    protected:
        HttpException http_exception;
        JsonException json_exception;
    };

    class AuthExepction : public APIException{
    public:
        using APIException::APIException;

        const char *what() const noexcept {
            http_exception.what();
            json_exception.what();
            return "API Exception: auth exception\n";
        }
    };

    class PageExepction : public APIException{
    public:
        using APIException::APIException;

        const char *what() const noexcept {
            http_exception.what();
            json_exception.what();
            return "API Exception: page exception\n";
        }
    };

    class UserExepction : public APIException{
    public:
        using APIException::APIException;

        const char *what() const noexcept {
            http_exception.what();
            json_exception.what();
            return "API Exception: user exception\n";
        }
    };

    class TestsExepction : public APIException{
    public:
        using APIException::APIException;

        [[nodiscard]] const char *what() const noexcept override {
            http_exception.what();
            json_exception.what();
            return "API Exception: tests exception\n";
        }
    };

}   // namespace APIException


// ---------- LAYER 1 | SERVER ----------


namespace ServerException {
    typedef HttpException::HttpException HttpException;
    typedef JsonException::JsonException JsonException;
    typedef APIException::APIException APIException;

    // Interface for all Server exceptions
    class ServerException : public std::runtime_error {
    public:
        using std::runtime_error::runtime_error;

        ServerException()
            : api_exception(),
              std::runtime_error("Server Exception") {}

        explicit ServerException(APIException& api_exception)
            : api_exception(api_exception),
              std::runtime_error("Server Exception") {}

        explicit ServerException(const char *msg)
                : api_exception(),
                  std::runtime_error(msg) {}

        explicit ServerException(const std::string& msg)
                : api_exception(),
                  std::runtime_error(msg) {}

    protected:
        APIException api_exception;
    };

    class RequestHandlerException : public ServerException {
    public:
        using ServerException::ServerException;
    };

    class APIGatewayException : public ServerException {
    public:
        using ServerException::ServerException;
        explicit APIGatewayException(boost::system::error_code& ec)
        : ec(ec),
                ServerException::ServerException("Listener Exception") {}

        APIGatewayException(const char* msg, boost::system::error_code& ec)
                : ec(ec),
                  ServerException::ServerException(msg) {}

        APIGatewayException(const std::string& msg, boost::system::error_code& ec)
                : ec(ec),
                  ServerException::ServerException(msg) {}

    protected:
        boost::system::error_code ec;
    };

    class ListenerException : public ServerException {
    public:
        using ServerException::ServerException;
        explicit ListenerException(boost::system::error_code& ec)
            : ec(ec),
              ServerException::ServerException("Listener Exception") {}

        ListenerException(const char* msg, boost::system::error_code& ec)
                : ec(ec),
                  ServerException::ServerException(msg) {}

        ListenerException(const std::string& msg, boost::system::error_code& ec)
                : ec(ec),
                  ServerException::ServerException(msg) {}

    protected:
        boost::system::error_code ec;
    };


}   // namespace ServerException


#endif //SERVER_V0_1_ERRORS_H