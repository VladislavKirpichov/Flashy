#ifndef CLIENT_USER_H
#define CLIENT_USER_H

#include<string>
#include<vector>
#include<iostream>

class User {
public:
    User();
    User(const std::string &_name, const std::string &_login, const std::string &_password, const std::string &_email);
    void set_id(const int& new_id){id = new_id;}
    void set_name(const std::string &new_name);

    void set_login(const std::string &new_login);

    void set_password(const std::string &new_password);

    void set_email(const std::string &new_email);

    void set_status(const std::string &new_status);

    void set_pages_id(const std::vector<std::string> &new_notes_id);

    void set_pages_titles(const std::vector<std::string> &new_notes_name);

    int get_id(){return id;}

    std::string get_name() const;

    std::string get_email() const;

    std::string get_login() const;

    std::string get_password() const;

    std::string get_status() const;

    std::vector<std::string> get_pages_id() const;

    std::vector<std::string> get_pages_titles() const;

private:
    int id;
    std::string name;
    std::string login;
    std::string password;
    std::string email;
    std::string status;
    std::vector<std::string> pages_id;
    std::vector<std::string> pages_titles;
};

#endif //CLIENT_USER_H
