#ifndef DB_TABLES_USERS_H_
#define DB_TABLES_USERS_H_
#include "DB.h"
#include <string>
#include <vector>
#include <stdlib.h>

class User {
private:
    int id;
    std::string name;
    std::string nickname;
    std::string password;
    std::string email;
    std::string status;
    DB *database;

public:

    User();

    User(std::string nick, std::string name, std::string pass, std::string email, std::string status);

    User(std::string nick);

    void user_connect_DB();

    void user_close_connect();

    void add_user();

    //void add_user(std::string nick, std::string pass, std::string email, std::string status);

    int get_user_ID() const;

    //std::vector<std::vector<std::string>> get_user_ID(std::string nick);

    //std::vector<std::vector<std::string>> get_all_user_info(int user_ID);

    //std::vector<std::vector<std::string>> get_all_user_info();

    void delete_user();

    std::string get_nick() const;

    void update_nick(std::string new_nick);

    std::string get_name() const;

    void update_name(std::string new_name);

    std::string get_pass() const;

    //std::vector<std::vector<std::string>> get_pass(size_t user_ID);

    void update_pass(std::string new_pass);

    std::string get_email() const;

    void update_email(std::string new_email);

    std::string get_status() const;

    void update_status(std::string new_status);

    std::vector<std::vector<std::string>> get_pages_id() const;

    std::vector<std::vector<std::string>> get_pages_title() const;

    std::vector<std::vector<std::string>> get_pages_file_paths() const;

    static bool find_user_nick(std::string nick, std::string pass);
};

#endif  // DB_TABLES_USERS_H_