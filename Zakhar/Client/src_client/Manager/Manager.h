#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#endif //CLIENT_MANAGER_H
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <string>
#include "Client.h"
#include "User.h"
#include "Note.h"
#include "Serializer.h"
namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;
class Manager{
public:
    //Manager(net::io_context &ioc);
    void Connect(std::string host, std::string port);
    void Auth(std::string Login, std::string Password);
    void Reg(std::string Login, std::string Password);
    void Get_Page(std::string page_id);
    void Update(std::string Update_message);
    void Exit();
private:
    User current_user;
    Note current_note;
    Serializer serializer;
    WebSocketClient * client;
};