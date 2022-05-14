//
// Created by vladislav on 14.05.22.
//

#ifndef SERVER_V0_1_PAGEMANAGERCREATOR_H
#define SERVER_V0_1_PAGEMANAGERCREATOR_H

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <iostream>
#include <memory>
#include <string>

#include "PageManager.hpp"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using error_code = boost::system::error_code;


template<typename Body, typename Allocator, typename Send>
class PageManagerCreator {
public:
    static std::shared_ptr<GetPageManager<Body, Allocator, Send>> create_GetPageManager(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send);

    /* --- ADD HERE NEW MANAGERS --- */
};

template<typename Body, typename Allocator, typename Send>
std::shared_ptr<GetPageManager<Body, Allocator, Send>>
PageManagerCreator<Body, Allocator, Send>::create_GetPageManager(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send) {
    return std::make_shared<GetPageManager<Body, Allocator, Send>>(std::move(req), std::forward<Send>(send));
}

#endif //SERVER_V0_1_PAGEMANAGERCREATOR_H