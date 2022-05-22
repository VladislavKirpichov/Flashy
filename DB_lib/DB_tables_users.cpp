#include "DB.h"
#include "DB_tables_users.h"

void User::user_connect_DB() {
    database = new DB("LAPTOP-9KQ1QFS1.local", "3306", "Admin", "123", "flashy");
}

void User::user_close_connect() {
    database->Close();
}
void User::add_user (std::string nick, std::string pass, std::string email, std::string status) {

    database->Insert("INSERT INTO users(nick,pass,email,status) VALUES (?, ?, ?, ?)", { "S:" + nick , "S:" + pass , "S:" + email, "S:" + status });
}

std::vector<std::vector<std::string>> User::get_user_ID(std::string nick){
    return database->Get("SELECT id FROM users WHERE nick=?", { "S:" + nick}, 1);
}
std::vector<std::vector<std::string>> User::get_all_user_info(size_t id){
    std::string ID = std::to_string(id);
    return database->Get("SELECT * FROM users WHERE id=?", {"I:"+ ID}, 5);
}

void User::delete_user(size_t id){
    std::string ID = std::to_string(id);
    database->Delete("DELETE FROM users WHERE id=?", { "I:" + ID});
}

std::vector<std::vector<std::string>> User::get_nick(size_t id){
    std::string ID = std::to_string(id);
    return database->Get("SELECT nick FROM users WHERE id=?", { "I:" + ID}, 1);
}

void User::update_nick(size_t id, std::string new_nick){
    std::string ID = std::to_string(id);
    database->Update("UPDATE users SET nick=? WHERE id=?", { "S:" + new_nick, "I:" + ID});
}

std::vector<std::vector<std::string>> User::get_pass(size_t id){
    std::string ID = std::to_string(id);
    return database->Get("SELECT pass FROM users WHERE id=?", { "I:" + ID}, 1);
}

void User::update_pass(size_t id, std::string new_pass){
    std::string ID = std::to_string(id);
    database->Update("UPDATE users SET pass=? WHERE id=?", { "S:" + new_pass, "I:" + ID});
}

std::vector<std::vector<std::string>> User::get_email(size_t id){
    std::string ID = std::to_string(id);
    return database->Get("SELECT email FROM users WHERE id=?", { "I:" + ID}, 1);
}

void User::update_email(size_t id, std::string new_email){
    std::string ID = std::to_string(id);
    database->Update("UPDATE users SET email=? WHERE id=?", { "S:" + new_email, "I:" + ID});
}

std::vector<std::vector<std::string>> User::get_status(size_t id){
    std::string ID = std::to_string(id);
    return database->Get("SELECT status FROM users WHERE id=?", { "I:" + ID}, 1);
}

void User::update_status(size_t id, std::string new_status){
    std::string ID = std::to_string(id);
    database->Update("UPDATE users SET status=? WHERE id=?", { "S:" + new_status, "I:" + ID});
}
