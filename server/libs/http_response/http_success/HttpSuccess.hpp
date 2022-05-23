//
// Created by vladislav on 22.05.22.
//

#ifndef SERVER_V0_1_HTTPSUCCESS_HPP
#define SERVER_V0_1_HTTPSUCCESS_HPP

#include <string>
#include <boost/beast.hpp>
#include <boost/beast/http.hpp>

#include "IHttpResponse.hpp"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>

template<typename Send>
class Ok200 : public IHttpResponse<http::string_body, Send> {
public:
    using IHttpResponse<http::string_body, Send>::IHttpResponse;
    void send_response() noexcept final {
        http::response<http::string_body> res{http::status::ok, this->get_response_version()};

        res.body() = "ok\n";
        this->set_response_filds(res);

        return this->get_send()(std::move(res));
    }
};

#endif //SERVER_V0_1_HTTPSUCCESS_HPP
