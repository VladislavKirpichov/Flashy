#include "DB_tables.h"

void User::add_user (std::string nick, std::string pass, std::string email, std::string status) {
    DB conn = DB("LAPTOP-9KQ1QFS1.local", "3306", "Admin", "123", "flashy");
    conn.Insert("INSERT INTO users(nick,pass,email,status) VALUES (?, ?, ?, ?)", { "S:" + nick , "S:" + pass , "S:" + email, "S:" + status });
    conn.Close();
}

std::vector<std::vector<std::string>> User::getID(std::string nick){
    DB conn = DB("LAPTOP-9KQ1QFS1.local", "3306", "Admin", "123", "flashy");
    return conn.Get("SELECT id FROM users WHERE nick=?", { "S:" + nick}, 1);
    conn.Close();
}
std::vector<std::vector<std::string>> User::get_all_user_info(size_t id){
    DB conn = DB("LAPTOP-9KQ1QFS1.local", "3306", "Admin", "123", "flashy");
    std::string ID = std::to_string(id);
    return conn.Get("SELECT * FROM users WHERE id=?", {"I:"+ ID}, 5);
    conn.Close();
}

void User::delete_user(size_t id){
    DB conn = DB("LAPTOP-9KQ1QFS1.local", "3306", "Admin", "123", "flashy");
    std::string ID = std::to_string(id);
    return conn.Delete("DELETE FROM users WHERE id=?", { "I:" + ID});
    conn.Close();
}

std::string User::get_nick(size_t id){
    DB conn = DB("LAPTOP-9KQ1QFS1.local", "3306", "Admin", "123", "flashy");
    std::string ID = std::to_string(id);
    return conn.Get("SELECT nick FROM users WHERE id=?", { "I:" + ID});
    conn.Close();
}

void User::set_nick(std::string){

}

void User::update_nick(std::string){

}

std::string User::get_pass(){

}

void User::update_pass(std::string){

}

std::string User::get_email(){

}

void User::update_email(std::string){

}

std::string User::get_status(){

}

void User::update_status(std::string){

}


Page::Page(size_t, time_t, time_t, time_t){

}


std::vector<std::vector<std::string>> Page::get_all_page_info(){

}

size_t Page::getID(){

}
        
size_t Page::get_userID(){

}

std::vector<std::vector<std::string>> Page::get_user_pages(){

}

void Page::delete_page(){

}

time_t Page::get_created_time(){

}

time_t Page::get_updated_time(){

}

void Page::update_updated_time(time_t){

}

Block::Block(std::string, size_t, size_t, std::string, size_t, size_t){

}

std::vector<std::vector<std::string>> Block::get_all_block_info(){

}

void Block::delete_block(){

}

std::string Block::get_type(){

}

std::string Block::get_block(){

}

std::vector<std::vector<std::string>> Block::get_page_blocks(){

}

Question::Question(size_t, std::string, std::string, std::string){

}

std::string Question::get_question(){

}

std::string Question::get_answer(){

}

void Question::update_answer(std::string){

}
