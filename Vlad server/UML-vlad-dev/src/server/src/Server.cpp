//
// Created by vladislav on 22.04.22.
//

#include "Server.h"

#include <boost/beast/core.hpp>
#include <iostream>
#include <vector>
#include <thread>

#define NUMBER_OF_THREADS 10

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

ServerManager::ServerManager() {
    _opts.ip = "127.0.0.1";
    _opts.port = 8080;
    _opts.owner = "server";
}

ServerManager::ServerManager(Options &opts) : _opts(opts) {}

void ServerManager::run() {
    /*
     * For now:
     * - single threaded
     * - single io_context
     * */

    net::io_context ioc;
    std::cout << "Listening on " << _opts.ip << ":" << _opts.port << std::endl;

    // Listener responsible for the life of the shared_ptr
    std::make_shared<Listener>(ioc, _opts.ip, _opts.port)->async_accept();

    // FOR MULTITHREAD SERVER
//    size_t n = NUMBER_OF_THREADS;
//    std::vector<std::thread> threads;
//    threads.reserve(n);
//
//    while (n--)
//        threads.emplace_back([&ioc](){ ioc.run(); }).detach();

    ioc.run();
    return;
}
