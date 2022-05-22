//
// Created by vladislav on 22.05.22.
//

#ifndef SERVER_V0_1_HTTPSUCCESS_HPP
#define SERVER_V0_1_HTTPSUCCESS_HPP

#include <string>
#include <boost/beast.hpp>
#include <boost/beast/http.hpp>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>

template<typename Send>
class HttpSuccess {
public:
    explicit HttpSuccess(Send&& send, unsigned response_version)
            : _response_version(response_version),
              _send(std::move(send)) {}

    virtual void send_response() noexcept = 0;

    Send _send;

protected:
    unsigned int get_response_version() { return this->_response_version; }
    void set_response_filds(http::response<http::string_body>& res) const;

private:
    unsigned int _response_version;
};

template<typename Send>
void HttpSuccess<Send>::set_response_filds(http::response<http::string_body>& res) const {
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/text");
    res.content_length(res.body().size());
}

template<typename Send>
class Ok200 : public HttpSuccess<Send> {
public:
    explicit Ok200(Send&& send, unsigned response_version) : HttpSuccess<Send>(std::move(send), response_version) {}
    void send_response() noexcept final {
        http::response<http::string_body> res{http::status::ok, this->get_response_version()};

        res.body() = "ok";
        this->set_response_filds(res);

        return this->_send(std::move(res));
    }
};

#endif //SERVER_V0_1_HTTPSUCCESS_HPP
