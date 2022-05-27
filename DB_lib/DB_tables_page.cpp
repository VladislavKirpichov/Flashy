#include "DB.h"
#include "DB_tables_page.h"

Page::Page(int user_ID, std::string theme, std::string title, std::string file)
    : user_id(user_ID), theme(theme), title(title), file(file)
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
    MyData = database->Get("SELECT * FROM page WHERE id=?", {"I:"+ ID}, 8);

    user_id = std::stoi(MyData[0][1]);
    theme = MyData[0][2];
    title = MyData[0][3];
    created_time = MyData[0][4];
    updated_time = MyData[0][5];
    last_visited_time = MyData[0][6];

    recommend_questions_id = database->Get("SELECT rec_question_1_id, rec_question_2_id, rec_question_3_id, rec_question_4_id, rec_question_5_id, rec_question_6_id, rec_question_7_id, rec_question_8_id, rec_question_9_id, rec_question_10_id FROM recommend_questions WHERE page_ID=?", { "I:"+ ID }, 10);

}

void Page::page_connect_DB() {
    database = new DB("LAPTOP-9KQ1QFS1.local", "3306", "Admin", "123", "flashy");
}

void Page::page_close_connect() {
    database->Close();
}

void Page::add_page(){
    std::string user_ID = std::to_string(user_id);
    database->Insert("INSERT INTO page(userID,title,file) VALUES (?, ?, ?, ?)", { "I:" + user_ID , "S:" + theme, "S:" + title , "S:" + file });
    std::vector<std::vector<std::string>> MyData = database->Get("SELECT id FROM page WHERE file=?", { "S:" + file}, 1);
    id = std::stoi(MyData[0][0]);
}

int Page::get_page_ID() const {
    //return database->Get("SELECT id FROM page WHERE title=?", { "S:" + page_title}, 1);
    return id;
}

std::vector<std::vector<std::string>> Page::get_all_page_info(size_t page_ID) const {
    std::string ID = std::to_string(page_ID);
    return database->Get("SELECT * FROM page WHERE id=?", { "I:" + ID}, 8);
}

std::vector<std::vector<std::string>> Page::get_all_user_pages_id() const {
    std::string user_ID = std::to_string(user_id);
    return database->Get("SELECT id FROM page WHERE userID=?", { "I:" + user_ID}, 1);
}

int Page::get_user_ID() const {
    //std::string ID = std::to_string(page_ID);
    //return database->Get("SELECT userID FROM page WHERE id=?", { "I:" + ID}, 1);
    return user_id;
}

std::string Page::get_theme() const {
    return theme;
}

void Page::update_theme(std::string new_theme) {
    std::string ID = std::to_string(id);
    database->Update("UPDATE page SET theme=? WHERE id=?", { "S:" + new_theme, "I:" + ID});
}

void Page::update_page_title(std::string new_title){
    std::string ID = std::to_string(id);
    database->Update("UPDATE page SET title=? WHERE id=?", { "S:" + new_title, "I:" + ID});
}

std::string Page::get_page_title() const {
    //std::string ID = std::to_string(page_ID);
    //return database->Get("SELECT title FROM page WHERE id=?", { "I:" + ID}, 1);
    return title;
}

std::string Page::get_created_time() const {
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

std::string Page::get_updated_time() const {
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

std::string Page::get_last_visited_time() const {
    //std::string ID = std::to_string(page_ID);
    //return database->Get("SELECT lastVisited FROM page WHERE id=?", { "I:" + ID}, 1);
    return last_visited_time;
}

void Page::update_file_page(std::string new_file){
    std::string ID = std::to_string(id);
    database->Update("UPDATE page SET file=? WHERE id=?", { "S:" + new_file, "I:" + ID});
    file = new_file;
}

std::string Page::get_file_page() const {
    //std::string ID = std::to_string(id);
    //return database->Get("SELECT file FROM page WHERE id=?", { "I:" + ID}, 1);
    return file;
}

std::vector<std::vector<std::string>> Page::get_rec_questions_id() const  {
    return recommend_questions_id;
}

void Page::set_rec_questions_id(int first, int second, int third, int forth, int fifth, int sixth, int seventh, int eighth, int nineth, int tenth) {
    std::string ID = std::to_string(id);
    std::string q_1 = std::to_string(first);
    std::string q_2 = std::to_string(second);
    std::string q_3 = std::to_string(third);
    std::string q_4 = std::to_string(forth);
    std::string q_5 = std::to_string(fifth);
    std::string q_6 = std::to_string(sixth);
    std::string q_7 = std::to_string(seventh);
    std::string q_8 = std::to_string(eighth);
    std::string q_9 = std::to_string(nineth);
    std::string q_10 = std::to_string(tenth);

    database->Insert("INSERT INTO recommend_questions(page_ID) VALUES (?)", { "I:" + ID });

    database->Update("UPDATE recommend_questions SET rec_question_1_id=?, rec_question_2_id=?, rec_question_3_id=?, rec_question_4_id=?, rec_question_5_id=?, rec_question_6_id=?, rec_question_7_id=?, rec_question_8_id=?, rec_question_9_id=?, rec_question_10_id=? WHERE page_ID=?", { "I:" + q_1, "I:" + q_2, "I:" + q_3, "I:" + q_4, "I:" + q_5, "I:" + q_6, "I:" + q_7, "I:" + q_8, "I:" + q_9, "I:" + q_10, "I:" + ID });

    recommend_questions_id = database->Get("SELECT rec_question_1_id, rec_question_2_id, rec_question_3_id, rec_question_4_id, rec_question_5_id, rec_question_6_id, rec_question_7_id, rec_question_8_id, rec_question_9_id, rec_question_10_id FROM recommend_questions WHERE page_ID=?", { "I:"+ ID }, 10);

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