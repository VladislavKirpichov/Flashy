#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <string>
#include "Manager.h"
#include <QApplication>
#include "startpage.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

int main(int argc, char *argv[]) {
    std::string host = "192.168.43.143";
    unsigned short port = 8080;
    Manager::get_instance()->set_destination(host, port);
    QApplication a(argc, argv);
    StartPage w;
    w.show();
    return a.exec();
}
