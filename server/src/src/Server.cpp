//
// Created by vladislav on 22.04.22.
//

#include "Server.h"

#include <boost/asio/ip/tcp.hpp>
#include <vector>
#include <thread>

#include "Logger.hpp"
#include "Exceptions.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

ServerManager::ServerManager() {
    _opts.ip = "192.168.43.143";
    _opts.port = 8080;
    _opts.owner = "src";
    _opts.machine_name = "LAPTOP-9KQ1QFS1.local";
}

ServerManager::ServerManager(Options &opts) : _opts(opts) {}

void ServerManager::run() {
    net::io_context ioc;

    // make endpoit
    tcp::endpoint endpoint{{net::ip::make_address(_opts.ip)}, _opts.port};

    // Listener responsible for the life of the shared_ptr
    try {
        std::make_shared<Listener>(ioc, std::move(endpoint))->async_accept();
    }
    catch (ServerException::ListenerException& ec) {
        Logger::Critical(__LINE__, __FILE__, ec.what());
        throw ServerException::ListenerException();
    }

    ioc.run();
}
