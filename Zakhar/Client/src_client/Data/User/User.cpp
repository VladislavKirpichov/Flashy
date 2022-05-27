#include "User.h"

User::User() {}

void User::set_name(const std::string &new_name) {
    name = new_name;
}

void User::set_login(const std::string &new_login) {
    login = new_login;
}

void User::set_password(const std::string &new_password) {
    password = new_password;
}

void User::set_email(const std::string &new_email) {
    email = new_email;
}

void User::set_status(const std::string &new_status) {
    status = new_status;
}

void User::set_pages_id(const std::vector<std::string> &new_pages_id) {
    pages_id = new_pages_id;
}

void User::set_pages_title(const std::vector<std::string> &new_pages_title) {
    pages_title = new_pages_title;
}

std::string User::get_name() const {
    return name;
}

std::string User::get_login() const {
    return login;
}

std::string User::get_password() const {
    return password;
}

std::string User::get_email() const {
    return email;
}

std::string User::get_status() const {
    return status;
}

std::vector<std::string> User::get_pages_id() const {
    return pages_id;
}

std::vector<std::string> User::get_pages_title() const {
    return pages_title;
}