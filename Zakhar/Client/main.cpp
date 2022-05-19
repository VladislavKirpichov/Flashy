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
    unsigned short port = 8080;
    auto const text = "Hello, VLAD!";

    std::string user_json_example = "{\n"
                                    "  \"user_id\": \"137\",\n"
                                    "  \"name\": \"Boris\",\n"
                                    "  \"login\": \"Boris17\",\n"
                                    "  \"password\": \"Demon123\",\n"
                                    "  \"categories\": [ \"2\", \"3\"],\n"
                                    "  \"notes_id\": [ \"12\", \"17\"],\n"
                                    "  \"notes_name\": [\"Example 1\", \"Example 2\"]\n"
                                    "}";
    std::string host = "127.0.0.1";
//    User example;
//    Serializer ser;
//    net::io_context ioc;
//    Manager::get_instance(ioc);
//    std::string json_from_vlad =  Manager::get_instance(ioc)->get_json(host,port);
//    example = ser.user_deserialize(json_from_vlad);
//    std::cout << ser.user_serialize(example);
    QApplication a(argc, argv);
    StartPage w;
    w.show();

    return a.exec();
    return 0;
}