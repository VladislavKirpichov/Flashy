//
// Created by vladislav on 22.04.22.
//

#include "Server.h"

#include <boost/beast/core.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <vector>
#include <thread>

#include "Logger.hpp"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

ServerManager::ServerManager() {
    _opts.ip = "127.0.0.1";
    _opts.port = 8080;
    _opts.owner = "server";
    _opts.machine_name = "LAPTOP-9KQ1QFS1.local";
}

ServerManager::ServerManager(Options &opts) : _opts(opts) {}

void ServerManager::run() {
    net::io_context ioc;

    // make endpoit
    tcp::endpoint endpoint{{net::ip::make_address(_opts.ip)}, _opts.port};

    // call to Listener
    // Listener responsible for the life of the shared_ptr
    std::make_shared<Listener>(ioc, std::move(endpoint))->async_accept();

    // FOR MULTITHREAD SERVER
//    size_t n = NUMBER_OF_THREADS;
//    std::vector<std::thread> threads;
//    threads.reserve(n);
//
//    while (n--)
//        threads.emplace_back([&ioc](){ ioc.run(); }).detach();

    ioc.run();
}
