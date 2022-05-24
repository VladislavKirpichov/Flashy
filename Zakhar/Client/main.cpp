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
                                    "  \"name\": \"Boris\",\n"
                                    "  \"login\": \"Boris17\",\n"
                                    "  \"email\": \"137\",\n"
                                    "  \"password\": \"Demon123\",\n"
                                    "  \"status\": \"Student\",\n"
                                    "  \"notes_id\": [ \"12\", \"17\"],\n"
                                    "  \"notes_name\": [\"Example 1\", \"Example 2\"]\n"
                                    "}";
    std::string json_from_vlad =  Manager::get_instance()->get_json(host,port);
    Manager::get_instance()->get_user_from_server(host,port);
    QApplication a(argc, argv);
    StartPage w;
    w.show();

    return a.exec();
//    return 0;
}
