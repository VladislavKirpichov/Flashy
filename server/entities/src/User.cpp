#include "DB.h"
#include "../include/User.h"

User::User()
{}

User::User(std::string nick, std::string name, std::string pass, std::string email, std::string status)
        : nickname(nick), name(name), password(pass), email(email), status(status)
{
    user_connect_DB();
}

User::User(std::string nick)
        :nickname(nick)
{
    user_connect_DB();


    std::vector<std::vector<std::string>> MyData = database->Get("SELECT id FROM users WHERE nick=?", { "S:" + nickname}, 1);
    id = std::stoi(MyData[0][0]);

    std::string ID = std::to_string(id);
    MyData = database->Get("SELECT * FROM users WHERE id=?", {"I:"+ ID}, 6);

    name = MyData[0][2];
    password = MyData[0][3];
    email = MyData[0][4];
    status = MyData[0][5];
}

void User::user_connect_DB() {
    database = new DB("LAPTOP-9KQ1QFS1.local", "3306", "Admin", "123", "flashy");
}

void User::user_close_connect() {
    database->Close();
}

void User::add_user() {
    database->Insert("INSERT INTO users(nick,name,pass,email,status) VALUES (?, ?, ?, ?, ?)", { "S:" + nickname , "S:" + name ,"S:" + password , "S:" + email, "S:" + status });
    std::vector<std::vector<std::string>> MyData = database->Get("SELECT id FROM users WHERE nick=?", { "S:" + nickname}, 1);
    id = std::stoi(MyData[0][0]);
}

int User::get_user_ID() {
    return id;
}

/*
std::vector<std::vector<std::string>> User::get_user_ID(std::string nick){
    return database->Get("SELECT id FROM users WHERE nick=?", { "S:" + nick}, 1);
}
*/
/*
std::vector<std::vector<std::string>> User::get_all_user_info(){
    //std::string ID = std::to_string(id);
    return database->Get("SELECT * FROM users WHERE id=?", {"I:"+ id}, 5);
}
*/

void User::delete_user(){
    std::string ID = std::to_string(id);
    database->Delete("DELETE FROM users WHERE id=?", { "I:" + ID});
}

std::string User::get_nick(){
    //std::string ID = std::to_string(id);
    //return database->Get("SELECT nick FROM users WHERE id=?", { "I:" + ID}, 1);
    return nickname;
}

void User::update_nick(std::string new_nick){
    std::string ID = std::to_string(id);
    database->Update("UPDATE users SET nick=? WHERE id=?", { "S:" + new_nick, "I:" + ID});
    nickname = new_nick;
}
std::string User::get_name() {
    return name;
}

void User::update_name(std::string new_name) {
    std::string ID = std::to_string(id);
    database->Update("UPDATE users SET name=? WHERE id=?", { "S:" + new_name, "I:" + ID});
    name = new_name;
}

std::string User::get_pass() {
    return password;
}
/*
std::vector<std::vector<std::string>> User::get_pass(size_t id){
    std::string ID = std::to_string(id);
    return database->Get("SELECT pass FROM users WHERE id=?", { "I:" + ID}, 1);
}
*/

void User::update_pass(std::string new_pass){
    std::string ID = std::to_string(id);
    database->Update("UPDATE users SET pass=? WHERE id=?", { "S:" + new_pass, "I:" + ID});
    password = new_pass;
}

std::string User::get_email(){
    //std::string ID = std::to_string(id);
    //return database->Get("SELECT email FROM users WHERE id=?", { "I:" + ID}, 1);
    return email;
}

void User::update_email(std::string new_email){
    std::string ID = std::to_string(id);
    database->Update("UPDATE users SET email=? WHERE id=?", { "S:" + new_email, "I:" + ID});
    email = new_email;
}

std::string User::get_status(){
    //std::string ID = std::to_string(id);
    //return database->Get("SELECT status FROM users WHERE id=?", { "I:" + ID}, 1);
    return status;
}

void User::update_status(std::string new_status){
    std::string ID = std::to_string(id);
    database->Update("UPDATE users SET status=? WHERE id=?", { "S:" + new_status, "I:" + ID});
    status = new_status;
}

std::vector<std::vector<std::string>> User::get_pages_id() {
    std::string userID = std::to_string(id);
    return database->Get("SELECT id FROM page WHERE userID=?", { "I:" + userID }, 1);
}

std::vector<std::vector<std::string>> User::get_pages_title() {
    std::string userID = std::to_string(id);
    return database->Get("SELECT title FROM page WHERE userID=?", { "I:" + userID }, 1);
}

bool User::find_user_nick(std::string nick, std::string pass) {
    DB *base = new DB("LAPTOP-9KQ1QFS1.local", "3306", "Admin", "123", "flashy");
    std::vector<std::vector<std::string>> MyData;
    MyData = base->Get("SELECT * FROM users WHERE nick=? AND pass=?", { "S:" + nick, "S:" + pass}, 6);
    base->Close();
    if(MyData.empty()) {
        return false;
    } else {
        return true;
    }





}

