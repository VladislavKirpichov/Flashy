#ifndef CLIENT_USER_H
#define CLIENT_USER_H

#include<string>
#include<vector>
#include<iostream>

class User {
public:
    User();

    void set_name(const std::string &new_name);

    void set_login(const std::string &new_login);

    void set_password(const std::string &new_password);

    void set_email(const std::string &new_email);

    void set_status(const std::string &new_status);

    void set_pages_id(const std::vector<unsigned int> &new_notes_id);

    void set_pages_title(const std::vector<std::string> &new_notes_name);

    std::string get_name() const;

    std::string get_email() const;

    std::string get_login() const;

    std::string get_password() const;

    std::string get_status() const;

    std::vector<unsigned int> get_pages_id() const;

    std::vector<std::string> get_pages_title() const;

private:
    std::string name;
    std::string login;
    std::string password;
    std::string email;
    std::string status;
    std::vector<unsigned int> pages_id;
    std::vector<std::string> pages_title;
};

#endif //CLIENT_USER_H
