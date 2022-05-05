#include "User.h"
User::User(): user_id(0){}
void User::Change_Name(std::string new_name){
    name = new_name;
}
void User::Change_Password(std::string new_password){
    password = new_password;
}
void User::Change_Categories(std::vector<std::string> new_categories){
    categories = new_categories;
}
std::string User::print(){
    return name;
}