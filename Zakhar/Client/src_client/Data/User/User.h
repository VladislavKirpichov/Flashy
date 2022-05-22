#ifndef CLIENT_USER_H
#define CLIENT_USER_H

#include<string>
#include<vector>
#include<iostream>

class User {
public:
    User();

    User(std::string _name, std::vector<std::string> _notes_name);

    void set_user_id(const unsigned int &new_user_id);

    void set_name(const std::string &new_name);

    void set_login(const std::string &new_login);

    void set_password(const std::string &new_password);

    void set_status(const std::string &new_status);

    void set_notes_id(const std::vector<unsigned int> &new_notes_id);

    void set_notes_name(const std::vector<std::string> &new_notes_name);
    unsigned int get_user_id();

    std::string get_name();

    std::string get_login();

    std::string get_password();

    std::string get_status();

    std::vector<unsigned int> get_notes_id();

    std::vector<std::string> get_notes_name();

private:
    unsigned int user_id;
    std::string name;
    std::string login;
    std::string password;
    std::string status;
    std::vector<unsigned int> notes_id;
    std::vector<std::string> notes_name;
};

#endif //CLIENT_USER_H
