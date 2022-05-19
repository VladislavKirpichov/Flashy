

#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <string>
namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = boost::beast::http;// from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;
class WebSocketClient{
public:
    WebSocketClient(net::io_context &ioc);
    void Connect(std::string &host, std::string &port);
    void Write(std::string text);
    void Read();
    void Disconnect();
    void data_to_string();
    void getResponse(const std::string& host,const unsigned short& port);

private:
    tcp::resolver resolver;
    websocket::stream<tcp::socket> ws;
    beast::tcp_stream stream;
    beast::flat_buffer buffer;

};
#endif //CLIENT_CLIENT_H
