#ifndef LISTENER_H
#define LISTENER_H


#include <thread>
#include <string>

#include <boost/beast/core.hpp>


class Listener : public std::enable_shared_from_this<Listener> {
public:
    Listener(boost::asio::io_context& ioc, const unsigned short port);
    
    void asyncAccept();

private:
    boost::asio::io_context& ioc;
    boost::asio::ip::tcp::acceptor acceptor;
};


#endif