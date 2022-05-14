#ifndef CLIENT_USER_H
#define CLIENT_USER_H
#include<string>
#include<vector>
#include<iostream>
class User{
public:
    User();
    User(std::string _name, std::vector<std::string> _notes_name);
    void Change_Name(std::string new_name);
    void Change_Password(std::string new_password);
    void Change_Categories(std::vector<unsigned short> new_categories);
//    void Set_user_id();
//    void Set_Name();
//    void Set_Password();
//    void Set_Categories();
//    void Set_notes_id();
//    void Set_notes_name();
    std::string print();
private:
    unsigned int user_id;
    std::string name;
    std::string login;
    std::string password;
    std::vector<unsigned short> categories;
    std::vector<unsigned int> notes_id;
    std::vector<std::string> notes_name;
};
#endif //CLIENT_USER_H
