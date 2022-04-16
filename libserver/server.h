#ifndef SERVER_H
#define SERVER_H


#include <thread>
#include <string>
#include <boost/beast/websocket.hpp>

#include "listener.h"

struct Options {
    std::string owner;
    std::string ip;
    unsigned short port;
};


class ServerManager {
public:
    ServerManager(boost::asio::io_context& ioc, Options& opts);

    void run();
    void stop();
    void restart();
    std::string get_ip();
    unsigned short get_port();
    bool is_running();
    void set_opts(Options opts);

private:
    Listener listener;

    bool started;
    Options opts;
};


#endif
