#include "DB_tables.h"

User::User (std::string a, std::string b, std::string c, std::string d){

}
size_t User::getID(){

}
std::vector<std::vector<std::string>> User::get_all_user_info(){

}

void User::delete_user(){

}

std::string User::get_nick(){

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
