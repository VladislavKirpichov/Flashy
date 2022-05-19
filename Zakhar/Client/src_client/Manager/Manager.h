#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <string>
#include "Client.h"
#include "Serializer.h"
#include "User.h"
#include "Note.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;
class Manager{
public:
    static Manager* get_instance(net::io_context &ioc) {
        static Manager instance(ioc);
        return &instance;
    }
    std::string get_json(const std::string& host,const unsigned short& port);
    void Auth(std::string Login, std::string Password);
    void Reg(std::string Login, std::string Password);
    void Get_Page(std::string page_id);
    void Update(std::string Update_message);
    void ChangeUser(const User & new_user);
private:
    Manager(net::io_context &ioc);
    HTTPClient client;
    User current_user;
    Note current_note;
    Serializer serializer;
};
#endif //CLIENT_MANAGER_H
