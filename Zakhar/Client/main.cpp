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
    unsigned short port = 8080;
    std::string user_json_example = "{\n"
                                    "  \"name\": \"moc_name\",\n"
                                    "  \"login\": \"moc_login\",\n"
                                    "  \"password\": \"moc_password\",\n"
                                    "  \"email\": \"moc@example.com\",\n"
                                    "  \"status\": \"Student\",\n"
                                    "  \"pages_id\": [ \"35\", \"358\"],\n"
                                    "  \"pages_title\": [\"Moc Page 1\", \"Moc Page 2\"]\n"
                                    "}";

    Manager::get_instance()->set_destination(host,port);
    //Manager::get_instance()->get_user_from_server("test_user");
    QApplication a(argc, argv);
    StartPage w;
    w.show();

    return a.exec();
    return 0;
}
