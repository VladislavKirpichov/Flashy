#include "Manager.h"

Manager::Manager(net::io_context &ioc) : client(HTTPClient(ioc)) {}

std::string Manager::get(const std::string &target) {
    return client.get_response(host, port, target);
}

bool Manager::post(const std::string &target, const std::string &body) {
    return client.post_request(host, port, target, body);
}

bool Manager::put(const std::string &target, const std::string &body) {
    return client.put_request(host, port, target, body);
}


void Manager::get_user_from_server(const std::string &login) {
    //std::string target = "/user/?login=" + login + "&password=" + password;
    std::string target = "/user?login=" + login; // Для старых версий сервера
    current_user = serializer.user_deserialize(get(target));
}

void Manager::get_page_from_server(const std::string &page_id) {
    std::string target = "/Page?page_id=" + page_id;
    current_page = serializer.page_deserialize(get(target));
}

bool Manager::post_user() {
    //std::string target = "/user/?login=" + current_user.get_login() + "&password=" + current_user.get_password();
    std::string target = "/user?login=" + current_user.get_login(); // Для старых версий сервера
    if(post(target, serializer.user_serialize(current_user)))
        return true;
    else
        return false;
}

bool Manager::post_page() {
    std::string target = "/Page?page_id=" + std::to_string(current_page.get_id());
    if(post(target, serializer.page_serialize(current_page)))
        return true;
    else
        return false;
}

bool Manager::put_user() {
    //std::string target = "/user/?login=" + current_user.get_login() + "&password=" + current_user.get_password();
    std::string target = "/user?login=" + current_user.get_login(); // Для старых версий сервера
    if(put(target, serializer.user_serialize(current_user)))
        return true;
    else
        return false;
}

bool Manager::put_page() {
    std::string target = "/Page?page_id=" + std::to_string(current_page.get_id());
    if(put(target, serializer.page_serialize(current_page)))
        return true;
    else
        return false;
}

bool Manager::auth(const std::string &login, const std::string &password) {
    std::string target = "/auth/?login=" + login + "&password=" + password;
    if (get(target) == "ok\n")
        return true;
    return false;
}

bool Manager::reg(const std::string &name, const std::string &login, const std::string &password,
                  const std::string &email) {
    User new_user;
    new_user.set_login(login);
    new_user.set_password(password);
    new_user.set_name(name);
    new_user.set_email(email);
    std::string request = serializer.user_serialize(new_user);
    std::string target = "/registration/?login=" + login;
    if (post(target, request))
        return true;
    return false;
}


void Manager::update(std::string update_message) {}

User &Manager::get_user() {
    return current_user;
}

Page &Manager::get_page() {
    return current_page;
}

void Manager::change_user(const User &new_user) {
    current_user = new_user;
}

void Manager::set_destination(const std::string &new_host, const unsigned short &new_port) {
    host = new_host;
    port = new_port;
}
