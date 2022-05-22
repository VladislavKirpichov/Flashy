#ifndef DB_TABLES_USERS_H_
#define DB_TABLES_USERS_H_
#include "DB.h"
#include <string>
#include <vector>
#include <stdlib.h>

class User {
    private:
        int id;
        std::string nickname;
        std::string password;
        std::string email;
        std::string status;
        DB *database;

    public:

        User();

        User(std::string nick, std::string pass, std::string email, std::string status);

        User(std::string nick);

        void user_connect_DB();

        void user_close_connect();

        void add_user();

        //void add_user(std::string nick, std::string pass, std::string email, std::string status);

        int get_user_ID_by_nick();

        //std::vector<std::vector<std::string>> get_user_ID(std::string nick);

        //std::vector<std::vector<std::string>> get_all_user_info(int user_ID);

        std::vector<std::vector<std::string>> get_all_user_info();

        void delete_user(int user_ID);

        std::vector<std::vector<std::string>> get_nick(size_t user_ID);

        void update_nick(size_t user_ID, std::string new_nick);

        std::vector<std::vector<std::string>> get_pass(size_t user_ID);

        void update_pass(size_t user_ID, std::string new_pass);

        std::vector<std::vector<std::string>> get_email(size_t user_ID);

        void update_email(size_t user_ID, std::string new_email);

        std::vector<std::vector<std::string>> get_status(size_t user_ID);

        void update_status(size_t user_ID, std::string new_status);

};

#endif  // DB_TABLES_USERS_H_