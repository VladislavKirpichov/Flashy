#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <string>
#include "Client.h"
#include "Serializer.h"
#include "Manager.h"
#include <QApplication>
#include "startpage.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>


int main(int argc, char *argv[]) {
    std::string host = "127.0.0.1";
    User example = User("Example user", {"Example note 1", "Example note 2", "Example note 3"});
    unsigned short port = 8080;
    auto const text = "Hello, VLAD!";
//    WebSocketClient client(ioc);
//    client.getResponce(host, port);
    net::io_context ioc;
    Manager manager(ioc);
    manager.ChangeUser(example);
    QApplication a(argc, argv);
    StartPage w;
    w.show();

    return a.exec();

}