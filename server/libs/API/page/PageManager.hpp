//
// Created by vladislav on 06.05.22.
//

#ifndef SERVER_V0_1_PAGEMANAGER_HPP
#define SERVER_V0_1_PAGEMANAGER_HPP

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <boost/asio/strand.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <cppconn/exception.h>

#include "IManager.hpp"
#include "Exceptions.h"
#include "HttpSuccessCreator.hpp"
#include "HttpServerErrorCreator.hpp"
#include "JsonSerializer.h"
#include "Storage.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using error_code = boost::system::error_code;


template<typename Body, typename Allocator, typename Send>
class IPageManager : public IManager<Body, Allocator, Send> {
public:
    using IManager<Body, Allocator, Send>::IManager;
    virtual void handle_request() = 0;

protected:
    virtual void set_flags(http::response<http::string_body>& response);
};

template<typename Body, typename Allocator, typename Send>
void IPageManager<Body, Allocator, Send>::set_flags(http::response<http::string_body>& response) {
    response.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    response.set(http::field::content_type, "text/text");
    response.keep_alive(this->get_request_keep_alive());
}


/*
 * The GET method requests a representation of the specified resource.
 * Requests using GET should only retrieve entities and should have no other effect.
*/


template<typename Body, typename Allocator, typename Send>
class GetPageManager : public IPageManager<Body, Allocator, Send> {
public:
    using IPageManager<Body, Allocator, Send>::IPageManager;
    virtual void handle_request() final;

protected:
    void set_flags(http::response<http::string_body> &response) noexcept override;
};

template<typename Body, typename Allocator, typename Send>
void GetPageManager<Body, Allocator, Send>::set_flags(http::response<http::string_body> &response) noexcept {
    response.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    response.keep_alive(this->get_request_keep_alive());
    response.content_length(response.body().size());
}

template<typename Body, typename Allocator, typename Send>
void GetPageManager<Body, Allocator, Send>::handle_request() {
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
        // TODO: реализовать хранилище файлов .txt и отдачу их через БД

        // Если есть метка content, то отдаем контент страницы
        if (args.find("content") != args.end()) {
            Storage storage{};
            response.body() = storage.get_file(args.at("page_id"));
            response.set(http::field::content_type, "text/text");
        }
        else {
            Page page{args.at("page_id")};
            response.body() = JsonSerializer::serialize_page(page);
            response.set(http::field::content_type, "text/json");
        }
    }
    catch (JsonException::JsonException& ec) {
        return HttpServerErrorCreator<Send>
                ::create_service_unavailable_503(std::move(this->get_send()), this->get_request_version())->send_response();
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
class PutPageManager : public IPageManager<Body, Allocator, Send> {
public:
    using IPageManager<Body, Allocator, Send>::IPageManager;
    void handle_request() final;
private:
    void create_new_page(const std::string& page_id, const std::unordered_map<std::string, std::vector<std::string>>& json);
};

template<typename Body, typename Allocator, typename Send>
void PutPageManager<Body, Allocator, Send>::create_new_page(const std::string& page_id, const std::unordered_map<std::string, std::vector<std::string>>& json) {
    Page page{std::stoi(json.at("user_id")[0]), json.at("theme")[0], json.at("title")[0], page_id};
    page.add_page();

//    if (json.find("questions") != json.end())
//        page.set_rec_questions_id(json.at("questions"));

    page.page_close_connect();
}

template<typename Body, typename Allocator, typename Send>
void PutPageManager<Body, Allocator, Send>::handle_request() {
    http::response<http::string_body> response{http::status::ok, this->get_request_version()};

    // get args from url
    std::unordered_map<std::string, std::string> args{};
    try {
        args = HttpParser::define_args_map(this->get_request_target());
        // args = this->get_args_url();
    }
    catch (HttpException::InvalidArguments& ec) {
        Logger::Error(__LINE__, __FILE__, ec.what());
        HttpClientErrorCreator<Send>::create_bad_request_400(std::forward<Send>(this->get_send()), this->get_request_version())->send_response();
        return;
    }

    try {
        // create new page in storage
        Storage storage{};
        std::string page_id = storage.create_file(args.at("login"), "");
        
        create_new_page(page_id, JsonSerializer::deserialize_in_vector(this->get_request_body_data()));
    }

    catch (JsonException::JsonException& ec) {
        return HttpServerErrorCreator<Send>
        ::create_service_unavailable_503(std::move(this->get_send()), this->get_request_version())->send_response();
    }
    catch (std::out_of_range& ec) {
        return HttpClientErrorCreator<Send>
        ::create_bad_request_400(std::move(this->get_send()), this->get_request_version())->send_response();
    }
    catch (APIException::PageException& ec) {
        return HttpClientErrorCreator<Send>
        ::create_not_found_404(std::move(this->get_send()), this->get_request_version())->send_response();
    }

    return HttpSuccessCreator<Send>::create_ok_200(std::move(this->get_send()), this->get_request_version())->send_response();
}


// POST


template<typename Body, typename Allocator, typename Send>
class PostPageManager : public IPageManager<Body, Allocator, Send> {
public:
    using IPageManager<Body, Allocator, Send>::IPageManager;
    void handle_request() final;
private:
    void set_page_fields(const std::string& page_id, const std::unordered_map<std::string, std::vector<std::string>>& json);
};

template<typename Body, typename Allocator, typename Send>
void PostPageManager<Body, Allocator, Send>::set_page_fields(const std::string& page_id, const std::unordered_map<std::string, std::vector<std::string>>& json) {
    Page page{page_id};

    if (json.find("theme") != json.end())
        page.update_theme(json.at("theme")[0]);
    if (json.find("title") != json.end())
        page.update_page_title(json.at("title")[0]);

    page.set_last_visited_time();
    page.set_updated_time();

    if (json.find("questions") != json.end())
        for (auto& i : json.at("questions"))
            page.add_one_rec_question_id(i);

    page.page_close_connect();
}

template<typename Body, typename Allocator, typename Send>
void PostPageManager<Body, Allocator, Send>::handle_request() {
    std::unordered_map<std::string, std::string> args{};
    try {
        args = HttpParser::define_args_map(this->get_request_target());
    }
    catch (HttpException::InvalidArguments& ec) {
        Logger::Error(__LINE__, __FILE__, ec.what());
        HttpClientErrorCreator<Send>::create_bad_request_400(std::forward<Send>(this->get_send()), this->get_request_version())->send_response();
        return;
    }

    http::response<http::string_body> response{http::status::ok, this->get_request_version()};

    try {
        if (args.find("content") != args.end()) {
            Storage storage{};
            storage.update_file_body(args.at("page_id"), this->get_request_body_data());
        }
        else {
            Page page{args.at("page_id")};
            set_page_fields(args.at("page_id"), JsonSerializer::deserialize_in_vector(this->get_request_body_data()));
        }
    }
    catch (JsonException::JsonException& ec) {
        return HttpServerErrorCreator<Send>
        ::create_service_unavailable_503(std::move(this->get_send()), this->get_request_version())->send_response();
    }
    catch (std::out_of_range& ec) {
        return HttpClientErrorCreator<Send>
        ::create_bad_request_400(std::move(this->get_send()), this->get_request_version())->send_response();
    }
    catch (sql::SQLException& ec) {
        return HttpClientErrorCreator<Send>
        ::create_not_found_404(std::move(this->get_send()), this->get_request_version())->send_response();
    }

    return HttpSuccessCreator<Send>::create_ok_200(std::move(this->get_send()), this->get_request_version())->send_response();
}


// DELETE


template<typename Body, typename Allocator, typename Send>
class DeletePageManager : public IPageManager<Body, Allocator, Send> {
public:
    using IPageManager<Body, Allocator, Send>::IPageManager;
    void handle_request() final;
};

// TODO: доделать delete
template<typename Body, typename Allocator, typename Send>
void DeletePageManager<Body, Allocator, Send>::handle_request() {
    // get args from url
    std::unordered_map<std::string, std::string> args{};
    try {
        args = HttpParser::define_args_map(this->get_request_target());
        // args = this->get_args_url();
    }
    catch (HttpException::InvalidArguments& ec) {
        Logger::Error(__LINE__, __FILE__, ec.what());
        HttpClientErrorCreator<Send>::create_bad_request_400(std::forward<Send>(this->get_send()), this->get_request_version())->send_response();
        return;
    }

    try {
        // Page page{};
        // page.delete_page(args.at("page_id));
        // TODO: удалить данные из БД
    }
    catch (std::out_of_range& ec) {
        return HttpClientErrorCreator<Send>
        ::create_bad_request_400(std::move(this->get_send()), this->get_request_version())->send_response();
    }

    return HttpSuccessCreator<Send>::create_ok_200(std::move(this->get_send()), this->get_request_version())->send_response();
}

#endif //SERVER_V0_1_PAGEMANAGER_HPP
