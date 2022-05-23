//
// Created by vladislav on 23.05.22.
//

#ifndef SERVER_V0_1_IHTTPRESPONSE_HPP
#define SERVER_V0_1_IHTTPRESPONSE_HPP

#include <string>
#include <boost/beast.hpp>
#include <boost/beast/http.hpp>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>

template<typename Body, typename Send>
class IHttpResponse {
public:
    explicit IHttpResponse(Send&& send, unsigned response_version = 11)
            : _response_version(response_version),
              _send(std::move(send)) {}

    virtual void send_response() noexcept = 0;

protected:
    virtual unsigned int get_response_version();
    void set_response_filds(http::response<http::string_body>& res);
    Send& get_send() { return this->_send; }

private:
    unsigned int _response_version;
    Send _send;
};

template<typename Body, typename Send>
void IHttpResponse<Body, Send>::set_response_filds(http::response<http::string_body>& res) {
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/text");
    res.content_length(res.body().size());
}

template<typename Body, typename Send>
unsigned int IHttpResponse<Body, Send>::get_response_version() {
    this->_response_version;
}

#endif //SERVER_V0_1_IHTTPRESPONSE_HPP
