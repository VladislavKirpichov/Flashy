//
// Created by vladislav on 24.05.22.
//

#ifndef SERVER_V0_1_USER_H
#define SERVER_V0_1_USER_H

#include <string>
#include <vector>

class User {
public:
    void user_connect_DB();
    void user_close_connect();
    void add_user(std::string& nick, std::string& pass, std::string& email, std::string& status);

    std::vector<std::vector<std::string>> get_user_ID(std::string& nick);

    std::vector<std::vector<std::string>> get_all_user_info(size_t user_ID);

    void delete_user(size_t user_ID);

    std::vector<std::vector<std::string>> get_nick(size_t user_ID);
    void update_nick(size_t user_ID, std::string new_nick);

    std::vector<std::vector<std::string>> get_pass(size_t user_ID);
    void update_pass(size_t user_ID, std::string& new_pass);

    std::vector<std::vector<std::string>> get_email(size_t user_ID);
    void update_email(size_t user_ID, std::string& new_email);

    std::vector<std::vector<std::string>> get_status(size_t user_ID);
    void update_status(size_t user_ID, std::string& new_status);

private:
    size_t id;
    std::string login;
    std::string password;
    std::string email;
    std::string status;
    // DB *database;
};

#endif //SERVER_V0_1_USER_H
