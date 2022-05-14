#include "DB.h"

void DB::add_page(size_t user_ID, std::string title, std::string file, std::string mime, std::string url){
    std::string ID = std::to_string(user_ID);
    Insert("INSERT INTO page(userID,title,file,mime,url) VALUES (?, ?, ?, ?, ?)", { "I:" + user_ID , "S:" + title , "S:" + mime, "S:" + url });
}

std::vector<std::vector<std::string>> DB::get_page_ID(std::string page_title){
    return Get("SELECT id FROM page WHERE title=?", { "S:" + page_title}, 1);
}

std::vector<std::vector<std::string>> DB::get_all_page_info(size_t page_ID){
    std::string ID = std::to_string(page_ID);
    return Get("SELECT * FROM page WHERE id=?", { "I:" + ID}, 9);
}

std::vector<std::vector<std::string>> DB::get_all_user_pages(size_t user_ID){
    std::string ID = std::to_string(user_ID);
    return Get("SELECT * FROM page WHERE userID=?", { "I:" + ID}, 9);
}

std::vector<std::vector<std::string>> DB::get_user_ID(size_t page_ID){
    std::string ID = std::to_string(page_ID);
    return Get("SELECT userID FROM page WHERE id=?", { "I:" + ID}, 1);
}

void DB::update_page_title(size_t page_ID, std::string new_title){
    std::string ID = std::to_string(page_ID);
    Update("UPDATE page SET title=? WHERE id=?", { "S:" + new_title, "I:" + ID});
}

std::vector<std::vector<std::string>> DB::get_page_title(size_t page_ID){
    std::string ID = std::to_string(page_ID);
    return Get("SELECT title FROM page WHERE id=?", { "I:" + ID}, 1);
}

std::vector<std::vector<std::string>> DB::get_created_time(size_t page_ID){
    std::string ID = std::to_string(page_ID);
    return Get("SELECT createdTime FROM page WHERE id=?", { "I:" + ID}, 1);
}

void DB::set_updated_time(size_t page_ID){
    std::string ID = std::to_string(page_ID);
    Execute("UPDATE page SET updatedTime=NOW() WHERE id=" + ID);
}

std::vector<std::vector<std::string>> DB::get_updated_time(size_t page_ID){
    std::string ID = std::to_string(page_ID);
    return Get("SELECT updatedTime FROM page WHERE id=?", { "I:" + ID}, 1);
}

void DB::set_last_visited_time(size_t page_ID){
    std::string ID = std::to_string(page_ID);
    Execute("UPDATE page SET lastVisited=NOW() WHERE id=" + ID);
}

std::vector<std::vector<std::string>> DB::get_last_visited_time(size_t page_ID){
    std::string ID = std::to_string(page_ID);
    return Get("SELECT lastVisited FROM page WHERE id=?", { "I:" + ID}, 1);
}

void DB::update_file_page(size_t page_ID, std::string new_file){
    std::string ID = std::to_string(page_ID);
    Update("UPDATE page SET file=? WHERE id=?", { "S:" + new_file, "I:" + ID});
}

std::vector<std::vector<std::string>> DB::get_file_page(size_t page_ID){
    std::string ID = std::to_string(page_ID);
    return Get("SELECT file FROM page WHERE id=?", { "I:" + ID}, 1);
}

void DB::update_page_mime(size_t page_ID, std::string new_mime){
    std::string ID = std::to_string(page_ID);
    Update("UPDATE page SET mime=? WHERE id=?", { "S:" + new_mime, "I:" + ID});
}

std::vector<std::vector<std::string>> DB::get_page_mime(size_t page_ID){
    std::string ID = std::to_string(page_ID);
    return Get("SELECT mime FROM page WHERE id=?", { "I:" + ID}, 1);
}

void DB::update_page_url(size_t page_ID, std::string new_url){
    std::string ID = std::to_string(page_ID);
    Update("UPDATE page SET url=? WHERE id=?", { "S:" + new_url, "I:" + ID});
}

std::vector<std::vector<std::string>> DB::get_page_url(size_t page_ID){
    std::string ID = std::to_string(page_ID);
    return Get("SELECT url FROM page WHERE id=?", { "I:" + ID}, 1);
}

void DB::delete_page(size_t page_ID){
    std::string ID = std::to_string(page_ID);
    Delete("DELETE FROM page WHERE id=?", { "I:" + ID});
}