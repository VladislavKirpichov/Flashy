//
// Created by vladislav on 22.04.22.
//

#ifndef SERVER_LISTENER_H
#define SERVER_LISTENER_H


#include <string>
#include <boost/beast/core.hpp>


class Listener : public std::enable_shared_from_this<Listener> {
public:
    Listener(boost::asio::io_context& ioc, const std::string& ip_address = "127.0.0.1", unsigned short port = 8083);
    ~Listener();

    void async_accept();
    void on_accept(boost::system::error_code& ec);

private:
    boost::asio::io_context& _ioc;
    boost::asio::ip::tcp::acceptor _acceptor;
    boost::asio::ip::tcp::socket _socket;
};


#endif //SERVER_LISTENER_H
