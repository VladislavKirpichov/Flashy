//
// Created by vladislav on 20.05.22.
//

#ifndef SERVER_V0_1_ERRORS_H
#define SERVER_V0_1_ERRORS_H

#include <stdexcept>


// ---------- LAYER 4.1 | HTTP ----------


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
    };

    class InvalidArguments : public HttpException {
    public:
        using HttpException::HttpException;
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

        const char *what() const noexcept { return "Json Exception\n"; }
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

        const char *what() const noexcept {
            http_exception.what();
            json_exception.what();
            return "API Exception: tests exception\n";
        }
    };

}

// ---------- LAYER 1 | SERVER ----------



#endif //SERVER_V0_1_ERRORS_H
