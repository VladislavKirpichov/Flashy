
// TODO: ПОДКЛЮЧИТЬ БД!


#include "DB.h"

void DB::add_user (std::string nick, std::string pass, std::string email, std::string status) {
    Insert("INSERT INTO users(nick,pass,email,status) VALUES (?, ?, ?, ?)", { "S:" + nick , "S:" + pass , "S:" + email, "S:" + status });
}

std::vector<std::vector<std::string>> DB::get_user_ID(std::string nick){
    return Get("SELECT id FROM users WHERE nick=?", { "S:" + nick}, 1);
}

std::vector<std::vector<std::string>> DB::get_all_user_info(size_t id){
    std::string ID = std::to_string(id);
    return Get("SELECT * FROM users WHERE id=?", {"I:"+ ID}, 5);
}

void DB::delete_user(size_t id){
    std::string ID = std::to_string(id);
    DB::Delete("DELETE FROM users WHERE id=?", { "I:" + ID});
}

std::vector<std::vector<std::string>> DB::get_nick(size_t id){
    std::string ID = std::to_string(id);
    return DB::Get("SELECT nick FROM users WHERE id=?", { "I:" + ID}, 1);
}

void DB::update_nick(size_t id, std::string new_nick){
    std::string ID = std::to_string(id);
    Update("UPDATE users SET nick=? WHERE id=?", { "S:" + new_nick, "I:" + ID});
}

std::vector<std::vector<std::string>> DB::get_pass(size_t id){
    std::string ID = std::to_string(id);
    return Get("SELECT pass FROM users WHERE id=?", { "I:" + ID}, 1);
}

void DB::update_pass(size_t id, std::string new_pass){
    std::string ID = std::to_string(id);
    Update("UPDATE users SET pass=? WHERE id=?", { "S:" + new_pass, "I:" + ID});
}

std::vector<std::vector<std::string>> DB::get_email(size_t id){
    std::string ID = std::to_string(id);
    return Get("SELECT email FROM users WHERE id=?", { "I:" + ID}, 1);
}

void DB::update_email(size_t id, std::string new_email){
    std::string ID = std::to_string(id);
    Update("UPDATE users SET email=? WHERE id=?", { "S:" + new_email, "I:" + ID});
}

std::vector<std::vector<std::string>> DB::get_status(size_t id){
    std::string ID = std::to_string(id);
    return Get("SELECT status FROM users WHERE id=?", { "I:" + ID}, 1);
}

void DB::update_status(size_t id, std::string new_status){
    std::string ID = std::to_string(id);
    Update("UPDATE users SET status=? WHERE id=?", { "S:" + new_status, "I:" + ID});
}

