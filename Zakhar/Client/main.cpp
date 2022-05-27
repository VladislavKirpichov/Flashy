#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <string>
#include "Manager.h"
#include <QApplication>
#include "startpage.h"
#include "Serializer.h"
#include "Page.h"

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

    std::string page_json_example = "{\n"
                                    "  \"id\": \"0\",\n"
                                    "  \"title\": \"moc_title\",\n"
                                    " \"theme\": \"0\",\n"
                                    "  \"login\": \"moc_login\",\n"
                                    "  \"created_time\": \"01:01:1970\",\n"
                                    "  \"updated_time\": \"01:01:1970\",\n"
                                    "  \"last_visited_time\": \"01:01:1970\",\n"
                                    "  \"text\": \"MOC_TEXT MOC_TEXT\",\n"
                                    "  \"questions_id\": [ \"1\", \"2\"]\n"
                                    "}";

    Manager::get_instance()->set_destination(host,port);
    Manager::get_instance()->reg("moc_name", "moc_login", "moc_password", "moc@example.com");
    QApplication a(argc, argv);
    StartPage w;
    w.show();

    return a.exec();
    return 0;
}
