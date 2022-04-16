#include "server.h"

class ServerManager {
public:
    ServerManager(boost::asio::io_context& ioc, Options& opts)
    : ioc(ioc), opts(opts) {}

    void set_opts(Options opts) {
        this->opts = std::move(opts);
    }

    void run() {
        std::make_shared<Listener>(opts.ip, opts.port)->asyncAccept();
    }

private:
    bool started;
    boost::asio::io_context& ioc;
    Options opts;
};
