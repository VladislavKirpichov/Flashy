//
// Created by vladislav on 22.04.22.
//

#ifndef SERVER_H
#define SERVER_H


#include <string>

#include "Listener.h"

struct Options {
    std::string owner;
    std::string ip;
    std::string machine_name;
    unsigned short port;
};


class ServerManager {
public:
    ServerManager();
    ServerManager(Options& opts);

    void run();
    void stop();
    void restart();
    std::string get_ip();
    unsigned short get_port();
    bool is_running();
    void set_opts(Options opts);

private:
    bool started{};
    Options _opts;
};

#endif //SERVER_SERVER_H
