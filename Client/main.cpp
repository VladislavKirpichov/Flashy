#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <string>
#include "Manager.h"
#include <QApplication>
#include "startpage.h"
#include "Serializer.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
std::string user_json_example = "{\n"
                                "  \"name\": \"moc_name\",\n"
                                "  \"login\": \"moc_login\",\n"
                                "  \"password\": \"moc_password\",\n"
                                "  \"email\": \"moc@example.com\",\n"
                                "  \"status\": \"Student\",\n"
                                "  \"pages_id\": [ \"35\", \"358\"],\n"
                                "  \"pages_titles\": [\"Moc Page 1\", \"Moc Page 2\", \"Moc Page 3\", \"Moc Page 4\", \"Moc Page 5\", \"Moc Page 6\", \"Moc Page 7\", \"Moc Page 8\", \"Moc Page 9\", \"Moc Page 10\", \"Moc Page 11\"]\n"
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
std::string question_json_example = "{\n"
                                    "  \"title\": \"Moc Question\",\n"
                                    "  \"answer\": \"Yes\",\n"
                                    " \"question_id\": \"0\",\n"
                                    "  \"page_id\": \"\"\n"
                                    "}";
int main(int argc, char *argv[]) {
    std::string host = "192.168.43.143";
    unsigned short port = 8080;
    Manager::get_instance()->set_destination(host,port);
    Serializer s;
    Manager::get_instance()->get_user() = s.user_deserialize(user_json_example);
    Manager::get_instance()->get_page() = s.page_deserialize(page_json_example);

    QApplication a(argc, argv);
    StartPage w;
    w.show();

    return a.exec();
    return 0;
}
