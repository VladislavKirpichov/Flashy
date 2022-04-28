//
// Created by zuhropenchik on 28.04.22.
//

#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#endif //CLIENT_CLIENT_H
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <string>
namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;
class WebSocketClient{
public:
    WebSocketClient(net::io_context &ioc);
    void Connect(std::string host, std::string port);
    void Write(std::string text);
    void Read();
    void Disconnect();
    void data_to_string();

private:
    tcp::resolver resolver;
    websocket::stream<tcp::socket> ws;
    beast::flat_buffer buffer;
};