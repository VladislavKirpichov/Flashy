#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <string>
#include "Client.h"
#include "Serializer.h"
#include <QApplication>
#include "startpage.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>


int main(int argc, char *argv[])
{
    std::string host = "127.0.0.1";
    auto const  port = "8080";
    auto const  text = "Hello, VLAD!";
    net::io_context ioc;
    std::cout << "Hello!\n";
    QApplication a(argc, argv);
    std::cout << "Hello!\n";
    StartPage w;
    w.show();
    WebSocketClient client = WebSocketClient(ioc);
//    client.Connect(host, port);
//    client.Write(text);
//    client.Read();
//    client.data_to_string();
//    client.Disconnect();
    std::cout << "Hello!\n";
    return a.exec();
}