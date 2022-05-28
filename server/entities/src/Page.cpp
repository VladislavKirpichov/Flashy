#include "DB.h"
#include "Page.h"

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

    recommend_questions_id = database->Get("SELECT rec_question_id FROM recommend_questions WHERE page_ID=?", { "I:" + ID}, 1);
}

void Page::page_connect_DB() {
    database = new DB("localhost", "3306", "vlad", "12345vV!", "Flashy");
}

void Page::page_close_connect() {
    database->Close();
}

void Page::add_page(){
    std::string user_ID = std::to_string(user_id);
    database->Insert("INSERT INTO page(userID,theme,title,file) VALUES (?, ?, ?, ?)", { "I:" + user_ID , "S:" + theme, "S:" + title , "S:" + file });
    std::vector<std::vector<std::string>> MyData = database->Get("SELECT id FROM page WHERE file=?", { "S:" + file}, 1);
    id = std::stoi(MyData[0][0]);
    std::string ID = std::to_string(id);
    //database->Insert("INSERT INTO recommend_questions(page_ID) VALUES (?)", { "I:" + ID });
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

void Page::add_one_rec_question_id(std::string q_id) {
    std::string ID = std::to_string(id);

    database->Insert("INSERT INTO recommend_questions(page_ID,rec_question_id) VALUES (?, ?)", { "I:" + ID , "I:" + q_id });

    //database->Update("UPDATE recommend_questions SET rec_question_1_id=?, rec_question_2_id=?, rec_question_3_id=?, rec_question_4_id=?, rec_question_5_id=?, rec_question_6_id=?, rec_question_7_id=?, rec_question_8_id=?, rec_question_9_id=?, rec_question_10_id=? WHERE page_ID=?", { "I:" + q[0], "I:" + q[1], "I:" + q[2], "I:" + q[3], "I:" + q[4], "I:" + q[5], "I:" + q[6], "I:" + q[7], "I:" + q[8], "I:" + q[9], "I:" + ID });

    //recommend_questions_id = database->Get("SELECT rec_question_1_id, rec_question_2_id, rec_question_3_id, rec_question_4_id, rec_question_5_id, rec_question_6_id, rec_question_7_id, rec_question_8_id, rec_question_9_id, rec_question_10_id FROM recommend_questions WHERE page_ID=?", { "I:"+ ID }, 10);
}

void Page::add_five_rec_questions_id(std::vector<std::string> q_id) {
    std::string ID = std::to_string(id);
    database->Insert("INSERT INTO recommend_questions(page_ID,rec_question_id) VALUES (?, ?), (?, ?), (?, ?), (?, ?), (?, ?)", { "I:" + ID , "I:" + q_id[0], "I:" + ID, "I:" + q_id[1], "I:" + ID, "I:" + q_id[2], "I:" + ID, "I:" + q_id[3], "I:" + ID, "I:" + q_id[4] });
    recommend_questions_id = database->Get("SELECT rec_question_id FROM recommend_questions WHERE page_ID=?", { "I:" + ID}, 1);
}


void Page::add_five_rec_questions_id(std::vector<std::vector<std::string>> q_id) {
    std::string ID = std::to_string(id);
    database->Insert("INSERT INTO recommend_questions(page_ID,rec_question_id) VALUES (?, ?), (?, ?), (?, ?), (?, ?), (?, ?)", { "I:" + ID , "I:" + q_id[1][0], "I:" + ID, "I:" + q_id[1][0], "I:" + ID, "I:" + q_id[2][0], "I:" + ID, "I:" + q_id[3][0], "I:" + ID, "I:" + q_id[4][0] });
    recommend_questions_id = database->Get("SELECT rec_question_id FROM recommend_questions WHERE page_ID=?", { "I:" + ID}, 1);
}

void Page::set_rec_question_mark(std::string q_id, std::string mark) {
    std::string ID = std::to_string(id);
    database->Update("UPDATE recommend_questions SET mark=? WHERE page_ID=? AND rec_question_id=?", { "I:" + mark, "I:" + ID, "I" + q_id});
}

std::string Page::get_rec_question_mark(std::string q_id) {
    std::string ID = std::to_string(id);
    std::vector<std::vector<std::string>> MyData = database->Get("SELECT mark FROM recommend_questions WHERE page_ID=? AND rec_question_id=?", { "I:" + ID, "I:" + q_id}, 1);
    return MyData[0][0];
}

std::vector<std::vector<std::string>> Page::get_all_rec_question_marks_and_id() {
    std::string ID = std::to_string(id);
    return database->Get("SELECT rec_question_id, mark FROM recommend_questions WHERE page_ID=?", { "I:" + ID}, 2);
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