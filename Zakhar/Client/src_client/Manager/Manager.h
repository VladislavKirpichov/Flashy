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
#include "Page.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;

class Manager {
public:
    static Manager *get_instance() {
        static net::io_context _ioc;
        static Manager _instance(_ioc);
        return &_instance;
    }

    static Manager *get_instance_initial(net::io_context &ioc) {
        static Manager _instance(ioc);
        return &_instance;
    }

    void get_user_from_server(const std::string &login);

    void get_page_from_server(const std::string &page_id);

    bool post_user();

    bool post_page();

    bool put_user();

    bool put_page();
    bool auth(const std::string &login, const std::string &password);

    bool reg(const std::string &name, const std::string &login, const std::string &password,
             const std::string &email);


    void update(std::string update_message);


    User& get_user();

    Page& get_page();

    void change_user(const User &new_user);

    void set_destination(const std::string &new_host, const unsigned short &new_port);

private:
    explicit Manager(net::io_context &ioc);

    std::string get(const std::string &target);

    bool post(const std::string &target, const std::string &body);

    bool put(const std::string &target, const std::string &body);

    HTTPClient client;
    User current_user;
    Page current_page;
    Serializer serializer;
    std::string host;
    unsigned short port;

};

#endif //CLIENT_MANAGER_H
