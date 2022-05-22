#include "DB.h"
#include "DB_tables_page.h"

void Page::page_connect_DB() {
    database = new DB("LAPTOP-9KQ1QFS1.local", "3306", "Admin", "123", "flashy");
}

void Page::page_close_connect() {
    database->Close();
}

void Page::add_page(size_t user_ID, std::string title, std::string file, std::string mime, std::string url){
    std::string ID = std::to_string(user_ID);
    database->Insert("INSERT INTO page(userID,title,file,mime,url) VALUES (?, ?, ?, ?, ?)", { "I:" + user_ID , "S:" + title , "S:" + mime, "S:" + url });
}

std::vector<std::vector<std::string>> Page::get_page_ID(std::string page_title){
    return database->Get("SELECT id FROM page WHERE title=?", { "S:" + page_title}, 1);
}

std::vector<std::vector<std::string>> Page::get_all_page_info(size_t page_ID){
    std::string ID = std::to_string(page_ID);
    return database->Get("SELECT * FROM page WHERE id=?", { "I:" + ID}, 9);
}

std::vector<std::vector<std::string>> Page::get_all_user_pages(size_t user_ID){
    std::string ID = std::to_string(user_ID);
    return database->Get("SELECT * FROM page WHERE userID=?", { "I:" + ID}, 9);
}

std::vector<std::vector<std::string>> Page::get_user_ID(size_t page_ID){
    std::string ID = std::to_string(page_ID);
    return database->Get("SELECT userID FROM page WHERE id=?", { "I:" + ID}, 1);
}

void Page::update_page_title(size_t page_ID, std::string new_title){
    std::string ID = std::to_string(page_ID);
    database->Update("UPDATE page SET title=? WHERE id=?", { "S:" + new_title, "I:" + ID});
}

std::vector<std::vector<std::string>> Page::get_page_title(size_t page_ID){
    std::string ID = std::to_string(page_ID);
    return database->Get("SELECT title FROM page WHERE id=?", { "I:" + ID}, 1);
}

std::vector<std::vector<std::string>> Page::get_created_time(size_t page_ID){
    std::string ID = std::to_string(page_ID);
    return database->Get("SELECT createdTime FROM page WHERE id=?", { "I:" + ID}, 1);
}

void Page::set_updated_time(size_t page_ID){
    std::string ID = std::to_string(page_ID);
    database->Execute("UPDATE page SET updatedTime=NOW() WHERE id=" + ID);
}

std::vector<std::vector<std::string>> Page::get_updated_time(size_t page_ID){
    std::string ID = std::to_string(page_ID);
    return database->Get("SELECT updatedTime FROM page WHERE id=?", { "I:" + ID}, 1);
}

void Page::set_last_visited_time(size_t page_ID){
    std::string ID = std::to_string(page_ID);
    database->Execute("UPDATE page SET lastVisited=NOW() WHERE id=" + ID);
}

std::vector<std::vector<std::string>> Page::get_last_visited_time(size_t page_ID){
    std::string ID = std::to_string(page_ID);
    return database->Get("SELECT lastVisited FROM page WHERE id=?", { "I:" + ID}, 1);
}

void Page::update_file_page(size_t page_ID, std::string new_file){
    std::string ID = std::to_string(page_ID);
    database->Update("UPDATE page SET file=? WHERE id=?", { "S:" + new_file, "I:" + ID});
}

std::vector<std::vector<std::string>> Page::get_file_page(size_t page_ID){
    std::string ID = std::to_string(page_ID);
    return database->Get("SELECT file FROM page WHERE id=?", { "I:" + ID}, 1);
}

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

void Page::delete_page(size_t page_ID){
    std::string ID = std::to_string(page_ID);
    database->Delete("DELETE FROM page WHERE id=?", { "I:" + ID});
}