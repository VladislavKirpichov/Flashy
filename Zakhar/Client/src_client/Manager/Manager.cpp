#include "Manager.h"

Manager::Manager(net::io_context &ioc) : client(HTTPClient(ioc)) {}

std::string Manager::get(const std::string &target) {
    return client.get_response(host, port, target);
}

void Manager::get_user_from_server(const std::string &login) {
    std::string target = "/user?login=" + login;
    current_user = serializer.user_deserialize(get(target));
}

bool Manager::auth(const std::string &login, const std::string &password) {
    std::string target = "/auth/?login=" + login + "&password=" + password;
    if (get(target) == "ok\n")
        return true;
    return false;
}

void Manager::reg(std::string login, std::string password) {}

void Manager::get_page(std::string page_id) {}

void Manager::update(std::string update_message) {}

User Manager::get_user() {
    return current_user;
}

void Manager::change_user(const User &new_user) {
    current_user = new_user;
}

void Manager::set_destination(const std::string &new_host,const unsigned short &new_port){
    host = new_host;
    port = new_port;
}
