//
// Created by vladislav on 22.05.22.
//

#ifndef SERVER_V0_1_IMANAGER_HPP
#define SERVER_V0_1_IMANAGER_HPP

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>

template<typename Body, typename Allocator, typename Send>
class IManager {
public:
    IManager(boost::beast::http::request<Body, boost::beast::http::basic_fields<Allocator>>&& request, Send&& send)
        : _send(std::move(send)),
          _request(std::move(request)) {}

protected:
    virtual unsigned int get_request_version();
    virtual std::string get_request_target();
    virtual std::string get_request_body_data();
    virtual bool get_request_keep_alive();

    Send& get_send();

private:
    Send _send;
    boost::beast::http::request<Body, boost::beast::http::basic_fields<Allocator>> _request;
};

template<typename Body, typename Allocator, typename Send>
unsigned int IManager<Body, Allocator, Send>::get_request_version() {
    this->_request.version();
}

template<typename Body, typename Allocator, typename Send>
std::string IManager<Body, Allocator, Send>::get_request_target() {
    return this->_request.base().target().template to_string();
}

template<typename Body, typename Allocator, typename Send>
std::string IManager<Body, Allocator, Send>::get_request_body_data() {
    return beast::buffers_to_string(this->_request.body().data());
}

template<typename Body, typename Allocator, typename Send>
bool IManager<Body, Allocator, Send>::get_request_keep_alive() {
    return this->_request.version();
}

template<typename Body, typename Allocator, typename Send>
Send &IManager<Body, Allocator, Send>::get_send() {
    return this->_send;
}


#endif //SERVER_V0_1_IMANAGER_HPP
