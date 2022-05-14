//
// Created by vladislav on 28.04.22.
//

#ifndef SERVER_V0_1_WEBSOCKET_CONNECTION_H
#define SERVER_V0_1_WEBSOCKET_CONNECTION_H

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/http.hpp>
#include <memory>

class websocket_connection : public std::enable_shared_from_this<websocket_connection> {
public:
    explicit websocket_connection(boost::asio::ip::tcp::socket&& socket);
    ~websocket_connection();

    void run(boost::beast::http::request<boost::beast::http::dynamic_body>&& req);
    void send(std::shared_ptr<std::string const>& ss);

    void on_accept(boost::system::error_code ec);
    void on_read(boost::system::error_code ec, size_t bytes_transferred);
    void on_write(boost::system::error_code ec);

private:
    boost::beast::websocket::stream<boost::beast::tcp_stream> _ws;
    boost::beast::flat_buffer _buffer;
};


#endif //SERVER_V0_1_WEBSOCKET_CONNECTION_H
