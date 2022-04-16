#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <boost/asio/io_context.hpp>

#include "libserver/server.h"

int main() {
    auto const port = 8080;
    boost::asio::io_context ioc{1};

    Options opts = {.ip = "172.0.0.1", .port=8080};

    std::make_shared<ServerManager>(ioc, opts)->run();

    ioc.run();
}
