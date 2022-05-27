#include "DB.h"
#include "Page.h"

Page::Page(int user_ID, std::string title, std::string file)
        : user_id(user_ID), title(title), file(file)
{
    page_connect_DB();
}

Page::Page(std::string file)
        : file(file)
{
    page_connect_DB();

    std::vector<std::vector<std::string>> MyData = database->Get("SELECT id FROM page WHERE file=?", { "S:" + file}, 1);
    id = std::stoi(MyData[0][0]);

    std::string ID = std::to_string(id);
    MyData = database->Get("SELECT * FROM page WHERE id=?", {"I:"+ ID}, 7);

    user_id = std::stoi(MyData[0][1]);
    title = MyData[0][2];
    created_time = MyData[0][3];
    updated_time = MyData[0][4];
    last_visited_time = MyData[0][5];
}

void Page::page_connect_DB() {
    database = new DB("localhost", "3306", "vlad", "12345vV!", "Flashy");
}

void Page::page_close_connect() {
    database->Close();
}

void Page::add_page(){
    std::string user_ID = std::to_string(user_id);
    database->Insert("INSERT INTO page(userID,title,file) VALUES (?, ?, ?)", { "I:" + user_ID , "S:" + title , "S:" + file });
    std::vector<std::vector<std::string>> MyData = database->Get("SELECT id FROM page WHERE file=?", { "S:" + file}, 1);
    id = std::stoi(MyData[0][0]);
}

int Page::get_page_ID(){
    //return database->Get("SELECT id FROM page WHERE title=?", { "S:" + page_title}, 1);
    return id;
}

std::vector<std::vector<std::string>> Page::get_all_page_info(size_t page_ID){
    std::string ID = std::to_string(page_ID);
    return database->Get("SELECT * FROM page WHERE id=?", { "I:" + ID}, 9);
}

std::vector<std::vector<std::string>> Page::get_all_user_pages_id(){
    std::string user_ID = std::to_string(user_id);
    return database->Get("SELECT id FROM page WHERE userID=?", { "I:" + user_ID}, 1);
}

int Page::get_user_ID(){
    //std::string ID = std::to_string(page_ID);
    //return database->Get("SELECT userID FROM page WHERE id=?", { "I:" + ID}, 1);
    return user_id;
}

void Page::update_page_title(std::string new_title){
    std::string ID = std::to_string(id);
    database->Update("UPDATE page SET title=? WHERE id=?", { "S:" + new_title, "I:" + ID});
}

std::string Page::get_page_title(){
    //std::string ID = std::to_string(page_ID);
    //return database->Get("SELECT title FROM page WHERE id=?", { "I:" + ID}, 1);
    return title;
}

std::string Page::get_created_time(){
    //std::string ID = std::to_string(id);
    //return database->Get("SELECT createdTime FROM page WHERE id=?", { "I:" + ID}, 1);
    return created_time;
}

void Page::set_updated_time(){
    std::string ID = std::to_string(id);
    database->Execute("UPDATE page SET updatedTime=NOW() WHERE id=" + ID);
    std::vector<std::vector<std::string>> MyData = database->Get("SELECT updatedTime FROM page WHERE id=?", { "I:" + ID}, 1);
    updated_time = MyData[0][0];
}

std::string Page::get_updated_time(){
    //std::string ID = std::to_string(page_ID);
    //return database->Get("SELECT updatedTime FROM page WHERE id=?", { "I:" + ID}, 1);
    return updated_time;
}

void Page::set_last_visited_time(){
    std::string ID = std::to_string(id);
    database->Execute("UPDATE page SET lastVisited=NOW() WHERE id=" + ID);
    std::vector<std::vector<std::string>> MyData = database->Get("SELECT lastVisited FROM page WHERE id=?", { "I:" + ID}, 1);
    updated_time = MyData[0][0];
}

std::string Page::get_last_visited_time(){
    //std::string ID = std::to_string(page_ID);
    //return database->Get("SELECT lastVisited FROM page WHERE id=?", { "I:" + ID}, 1);
    return last_visited_time;
}

void Page::update_file_page(std::string new_file){
    std::string ID = std::to_string(id);
    database->Update("UPDATE page SET file=? WHERE id=?", { "S:" + new_file, "I:" + ID});
    file = new_file;
}

std::string Page::get_file_page(){
    //std::string ID = std::to_string(id);
    //return database->Get("SELECT file FROM page WHERE id=?", { "I:" + ID}, 1);
    return file;
}

/*
void Page::update_page_mime(size_t page_ID, std::string new_mime){
    std::string ID = std::to_string(page_ID);
    database->Update("UPDATE page SET mime=? WHERE id=?", { "S:" + new_mime, "I:" + ID});
}

std::vector<std::vector<std::string>> Page::get_page_mime(size_t page_ID){
    std::string ID = std::to_string(page_ID);
    return database->Get("SELECT mime FROM page WHERE id=?", { "I:" + ID}, 1);
}

void Page::update_page_url(size_t page_ID, std::string new_url){
    std::string ID = std::to_string(page_ID);
    database->Update("UPDATE page SET url=? WHERE id=?", { "S:" + new_url, "I:" + ID});
}

std::vector<std::vector<std::string>> Page::get_page_url(size_t page_ID){
    std::string ID = std::to_string(page_ID);
    return database->Get("SELECT url FROM page WHERE id=?", { "I:" + ID}, 1);
}

*/

void Page::delete_page(){
    std::string ID = std::to_string(id);
    database->Delete("DELETE FROM page WHERE id=?", { "I:" + ID});
}