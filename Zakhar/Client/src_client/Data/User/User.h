#ifndef CLIENT_USER_H
#define CLIENT_USER_H
#include<string>
#include<vector>
#include<iostream>
class User{
public:
    User();
    void Change_Name(std::string new_name);
    void Change_Password(std::string new_password);
    void Change_Categories(std::vector<std::string> new_categories);
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
    std::string password;
    std::vector<std::string> categories;
    std::vector<unsigned int> notes_id;
    std::vector<std::string> notes_name;
};
#endif //CLIENT_USER_H
