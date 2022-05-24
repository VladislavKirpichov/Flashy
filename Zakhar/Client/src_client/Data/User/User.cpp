#include "User.h"

User::User() {}

User::User(std::string _name, std::vector<std::string> _notes_name) {
    name = _name;
    notes_name = _notes_name;
}


void User::set_name(const std::string &new_name){
    name = new_name;
}

void User::set_login(const std::string &new_login){
    login = new_login;
}
void User::set_email(const std::string &new_email){
    email = new_email;
}

void User::set_password(const std::string &new_password){
    password = new_password;
}

void User::set_status(const std::string &new_status){
    status = new_status;
}

void User::set_notes_id(const std::vector<unsigned int> &new_notes_id){
    notes_id = new_notes_id;
}

void User::set_notes_name(const std::vector<std::string> &new_notes_name){
    notes_name = new_notes_name;
}



std::string User::get_name() {
    return name;
}

std::string User::get_login() {
    return login;
}

std::string User::get_email() {
    return email;
}

std::string User::get_password() {
    return password;
}

std::string User::get_status() {
    return status;
}

std::vector<unsigned int> User::get_notes_id() {
    return notes_id;
}

std::vector<std::string> User::get_notes_name() {
    return notes_name;
}