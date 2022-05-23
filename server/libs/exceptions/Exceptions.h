//
// Created by vladislav on 20.05.22.
//

#ifndef SERVER_V0_1_ERRORS_H
#define SERVER_V0_1_ERRORS_H

#include <stdexcept>
#include <boost/system/error_code.hpp>
#include "nlohmann/json.hpp"
#include "nlohmann/detail/exceptions.hpp"


// ---------- LAYER 4 | DB ----------


// TODO: сделать исключения для БД
//namespace DbExceptions {
//    // Interface for all HTTP exceptions
//    class HttpException : public std::runtime_error {
//    public:
//        HttpException() : std::runtime_error("Http Parser Exception") {}
//        explicit HttpException(const char* msg) : std::runtime_error("Http Parser Exception: " + std::string(msg)) {}
//        explicit HttpException(std::string const& msg) : std::runtime_error("Http Parser Exception: " + msg) {}
//        using std::runtime_error::runtime_error;
//    };
//}


// ---------- LAYER 3.1 | HTTP ----------


namespace HttpException {
    // Interface for all HTTP exceptions
    class HttpException : public std::runtime_error {
    public:
        HttpException() : std::runtime_error("Http Parser Exception") {}
        explicit HttpException(const char* msg) : std::runtime_error("Http Parser Exception: " + std::string(msg)) {}
        explicit HttpException(std::string const& msg) : std::runtime_error("Http Parser Exception: " + msg) {}
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

// TODO: Добавить исключения к JsonException

namespace JsonException {
    // Interface for all JSON exceptions
    class JsonException : public std::runtime_error {
    public:
        JsonException() : std::runtime_error("Json Exception") {}

        explicit JsonException(nlohmann::json::exception &ec) : std::runtime_error(
                std::string("nlohmann json error: ") + ec.what()) {}

        explicit JsonException(std::string &msg) : std::runtime_error(msg) {}

        using std::runtime_error::runtime_error;
    };
}


// ---------- LAYER 2 | API ----------

// TODO: Изменить классы дочерние от APIException

namespace APIException {
    using HttpException = HttpException::HttpException;
    using JsonException = JsonException::JsonException;

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

    class AuthException : public APIException{
    public:
        using APIException::APIException;

        const char *what() const noexcept {
            http_exception.what();
            json_exception.what();
            return "API Exception: auth exception\n";
        }
    };

    class PageException : public APIException{
    public:
        using APIException::APIException;

        const char *what() const noexcept {
            http_exception.what();
            json_exception.what();
            return "API Exception: page exception\n";
        }
    };

    class UserException : public APIException{
    public:
        using APIException::APIException;

        const char *what() const noexcept {
            http_exception.what();
            json_exception.what();
            return "API Exception: user exception\n";
        }
    };

    class TestsException : public APIException{
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
    using HttpException = HttpException::HttpException;
    using JsonException = JsonException::JsonException;
    using APIException = APIException::APIException;

    // Interface for all Server exceptions
    class ServerException : public std::runtime_error {
    public:
        using std::runtime_error::runtime_error;

        ServerException()
            : std::runtime_error("Server Exception") {}

        explicit ServerException(APIException& api_exception)
            : std::runtime_error("Server Exception"),
              api_exception(api_exception) {}

        explicit ServerException(const char *msg)
                : std::runtime_error(msg) {}

        explicit ServerException(const std::string& msg)
                : std::runtime_error(msg) {}

        ServerException(const ServerException& ec)
                : std::runtime_error(std::string(ec.what()) + std::string("Server Exception\n")) {}

    private:
        APIException api_exception{};
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

        APIGatewayException(const ServerException& ec)
                : ec(),
                  ServerException::ServerException("APIGatewayException\n") {}

    private:
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

    private:
        boost::system::error_code ec;
    };


}   // namespace ServerException


#endif //SERVER_V0_1_ERRORS_H
