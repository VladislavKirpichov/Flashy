//
// Created by vladislav on 28.05.22.
//

#ifndef SERVER_V0_1_QUESTIONMANAGER_HPP
#define SERVER_V0_1_QUESTIONMANAGER_HPP

#include "IManager.hpp"
#include "Exceptions.h"
#include "HttpSuccessCreator.hpp"
#include "HttpServerErrorCreator.hpp"
#include "HttpClientErrorCreator.hpp"
#include "HttpParser.h"
#include "JsonSerializer.h"
#include "Storage.h"
#include "Question.h"
#include "Logger.hpp"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using error_code = boost::system::error_code;

template<typename Body, typename Allocator, typename Send>
class GetQuestionManager : public IManager<Body, Allocator, Send> {
public:
    using IManager<Body, Allocator, Send>::IManager;
    virtual void handle_request() final;
protected:
    virtual void set_flags(http::response<http::string_body>& response);
};

template<typename Body, typename Allocator, typename Send>
void GetQuestionManager<Body, Allocator, Send>::set_flags(http::response<http::string_body>& response) {
    response.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    response.set(http::field::content_type, "application/json");
    response.keep_alive(this->get_request_keep_alive());
}

template<typename Body, typename Allocator, typename Send>
void GetQuestionManager<Body, Allocator, Send>::handle_request() {
    http::response<http::string_body> response{http::status::ok, this->get_request_version()};

    std::unordered_map<std::string, std::string> args{};
    try {
        args = HttpParser::define_args_map(this->get_request_target());
    }
    catch (HttpException::InvalidArguments& ec) {
        Logger::Error(__LINE__, __FILE__, ec.what());
        HttpClientErrorCreator<Send>::create_bad_request_400(std::forward<Send>(this->get_send()), this->get_request_version())->send_response();
        return;
    }

    try {
        Question question{std::stoi(args.at("question_id"))};
        response.body() = JsonSerializer::serialize_question(question);
        question.question_close_connect();
    }
    catch (JsonException::JsonException& ec) {
        return HttpServerErrorCreator<Send>
        ::create_service_unavailable_503(std::move(this->get_send()), this->get_request_version())->send_response();
    }
    catch (sql::SQLException& ec) {
        return HttpClientErrorCreator<Send>
        ::create_not_found_404(std::move(this->get_send()), this->get_request_version())->send_response();
    }
    catch (std::out_of_range& ec) {
        return HttpClientErrorCreator<Send>
        ::create_bad_request_400(std::move(this->get_send()), this->get_request_version())->send_response();
    }
    catch (APIException::PageException& ec) {
        return HttpClientErrorCreator<Send>
        ::create_not_found_404(std::move(this->get_send()), this->get_request_version())->send_response();
    }

    this->set_flags(response);
    return this->get_send()(std::move(response));
}


// PUT


template<typename Body, typename Allocator, typename Send>
class PutQuestionManager : public IManager<Body, Allocator, Send> {
public:
    using IManager<Body, Allocator, Send>::IManager;
    virtual void handle_request() final;
protected:
    virtual void set_flags(http::response<http::string_body>& response);
    Question create_new_question(int page_id, const std::unordered_map<std::string, std::string>& json);
};

template<typename Body, typename Allocator, typename Send>
void PutQuestionManager<Body, Allocator, Send>::set_flags(http::response<http::string_body>& response) {
    response.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    response.set(http::field::content_type, "text/text");
    response.keep_alive(this->get_request_keep_alive());
}

template<typename Body, typename Allocator, typename Send>
Question PutQuestionManager<Body, Allocator, Send>::create_new_question(int page_id, const std::unordered_map<std::string, std::string>& json) {
    Question question{page_id, json.at("title"), json.at("answer")};
    question.add_question();
    return question;
}

template<typename Body, typename Allocator, typename Send>
void PutQuestionManager<Body, Allocator, Send>::handle_request() {
    std::unordered_map<std::string, std::string> args{};
    try {
        args = HttpParser::define_args_map(this->get_request_target());
    }
    catch (HttpException::InvalidArguments& ec) {
        Logger::Error(__LINE__, __FILE__, ec.what());
        HttpClientErrorCreator<Send>::create_bad_request_400(std::forward<Send>(this->get_send()), this->get_request_version())->send_response();
        return;
    }

    try {
        auto json = JsonSerializer::deserialize(this->get_request_body_data());
        Question question = create_new_question(std::stoi(args.at("page_id")), json);

        http::response<http::string_body> response{http::status::ok, this->get_request_version()};
        response.body() = std::to_string(question.get_question_ID());
        this->set_flags(response);

        question.question_close_connect();
        return this->get_send()(std::move(response));
    }
    catch (JsonException::JsonException& ec) {
        return HttpServerErrorCreator<Send>
        ::create_service_unavailable_503(std::move(this->get_send()), this->get_request_version())->send_response();
    }
    catch (sql::SQLException& ec) {
        return HttpClientErrorCreator<Send>
        ::create_not_found_404(std::move(this->get_send()), this->get_request_version())->send_response();
    }
    catch (std::out_of_range& ec) {
        return HttpClientErrorCreator<Send>
        ::create_bad_request_400(std::move(this->get_send()), this->get_request_version())->send_response();
    }
    catch (APIException::PageException& ec) {
        return HttpClientErrorCreator<Send>
        ::create_not_found_404(std::move(this->get_send()), this->get_request_version())->send_response();
    }
}


// POST


template<typename Body, typename Allocator, typename Send>
class PostQuestionManager : public IManager<Body, Allocator, Send> {
public:
    using IManager<Body, Allocator, Send>::IManager;
    virtual void handle_request() final;
protected:
    void set_question_fields(int question_id, const std::unordered_map<std::string, std::string>& json);
};

template<typename Body, typename Allocator, typename Send>
void PostQuestionManager<Body, Allocator, Send>::set_question_fields(int question_id, const std::unordered_map<std::string, std::string> &json) {
    Question question{question_id};

    if (json.find("title") != json.end())
        question.update_question_file(json.at("title"));
    if (json.find("answer") != json.end())
        question.update_question_answer(json.at("answer"));

    question.question_close_connect();
}

template<typename Body, typename Allocator, typename Send>
void PostQuestionManager<Body, Allocator, Send>::handle_request() {
    std::unordered_map<std::string, std::string> args{};
    try {
        args = HttpParser::define_args_map(this->get_request_target());
    }
    catch (HttpException::InvalidArguments& ec) {
        Logger::Error(__LINE__, __FILE__, ec.what());
        HttpClientErrorCreator<Send>::create_bad_request_400(std::forward<Send>(this->get_send()), this->get_request_version())->send_response();
    }

    try {
        if (args.find("like") == args.end()) {
            set_question_fields(std::stoi(args.at("question_id")), JsonSerializer::deserialize(this->get_request_body_data()));
            return HttpSuccessCreator<Send>::create_ok_200(std::move(this->get_send()), this->get_request_version())->send_response();
        }
        else {
            Question question{std::stoi(args.at("question_id"))};
            question.set_rec_question_mark(args.at("page_id"), "1");
            question.question_close_connect();
            return HttpSuccessCreator<Send>::create_ok_200(std::move(this->get_send()), this->get_request_version())->send_response();
        }
    }
    catch (JsonException::JsonException& ec) {
        return HttpServerErrorCreator<Send>
        ::create_service_unavailable_503(std::move(this->get_send()), this->get_request_version())->send_response();
    }
    catch (sql::SQLException& ec) {
        return HttpClientErrorCreator<Send>
        ::create_not_found_404(std::move(this->get_send()), this->get_request_version())->send_response();
    }
    catch (std::out_of_range& ec) {
        return HttpClientErrorCreator<Send>
        ::create_bad_request_400(std::move(this->get_send()), this->get_request_version())->send_response();
    }
    catch (APIException::PageException& ec) {
        return HttpClientErrorCreator<Send>
        ::create_not_found_404(std::move(this->get_send()), this->get_request_version())->send_response();
    }
}


#endif //SERVER_V0_1_QUESTIONMANAGER_HPP