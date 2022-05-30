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
                                "  \"id\": \"2\",\n"
                                "  \"name\": \"Zakhar\",\n"
                                "  \"login\": \"Zakhar123\",\n"
                                "  \"password\": \"moc_password\",\n"
                                "  \"email\": \"moc@example.com\",\n"
                                "  \"status\": \"Student\",\n"
                                "  \"pages_id\": [ \"1\", \"2\"],\n"
                                "  \"pages_titles\": [\"Math\", \"C++\"]\n"
                                "}";

std::string page_json_example1 = "{\n"
                                 "  \"id\": \"1\",\n"
                                 "  \"user_id\": \"2\",\n"
                                 "  \"title\": \"Math\",\n"
                                 " \"theme\": \"0\",\n"
                                 "  \"login\": \"moc_login\",\n"
                                 "  \"created_time\": \"16:05:2022\",\n"
                                 "  \"updated_time\": \"29:05:2022\",\n"
                                 "  \"last_visited_time\": \"30:05:2022\",\n"
                                 "  \"text\": \"Mathematics is an area of knowledge that includes such topics as numbers , formulas and related structures, shapes and the spaces in which they are contained , and quantities and their changes. There is no general consensus about its exact scope or epistemological status.\",\n"
                                 "  \"questions_id\": [ \"1\", \"2\"]\n"
                                 "}";
std::string page_json_example2 = "{\n"
                                 "  \"id\": \"1\",\n"
                                 "  \"user_id\": \"2\",\n"
                                 "  \"title\": \"C++\",\n"
                                 " \"theme\": \"0\",\n"
                                 "  \"login\": \"moc_login\",\n"
                                 "  \"created_time\": \"01:01:1970\",\n"
                                 "  \"updated_time\": \"01:01:1970\",\n"
                                 "  \"last_visited_time\": \"01:01:1970\",\n"
                                 "  \"text\": \"MOC_TEXT MOC_TEXT\",\n"
                                 "  \"questions_id\": [ \"1\", \"2\"]\n"
                                 "}";
std::string question_json_example1 = "{\n"
                                     "  \"title\": \"What is 2+2\",\n"
                                     "  \"answer\": \"4\",\n"
                                     " \"question_id\": \"0\",\n"
                                     "  \"page_id\": \"1\"\n"
                                     "}";
std::string question_json_example2 = "{\n"
                                     "  \"title\": \"2+2*2\",\n"
                                     "  \"answer\": \"6\",\n"
                                     " \"question_id\": \"0\",\n"
                                     "  \"page_id\": \"2\"\n"
                                     "}";

int main(int argc, char *argv[]) {
    std::string host = "192.168.43.143";
    unsigned short port = 8080;
    Manager::get_instance()->set_destination(host, port);
    Serializer s;
    Manager::get_instance()->get_user() = s.user_deserialize(user_json_example);
    Manager::get_instance()->get_page() = s.page_deserialize(page_json_example1);

    Question temp = s.question_deserialize(question_json_example1);
    Manager::get_instance()->get_questions().push_back(temp);
    temp =s.question_deserialize(question_json_example2);
    Manager::get_instance()->get_questions().push_back(temp);

    QApplication a(argc, argv);
    StartPage w;
    w.show();

    return a.exec();
    return 0;
}
