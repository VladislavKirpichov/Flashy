#include "DB.h"
#include "DB_tables_question.h"

void Question::page_connect_DB() {
    database = new DB("LAPTOP-9KQ1QFS1.local", "3306", "Admin", "123", "flashy");
}

void Question::page_close_connect() {
    database->Close();
}

void Question::add_question(size_t page_ID, std::string file, std::string url, std::string answer){
    std::string ID = std::to_string(page_ID);
    database->Insert("INSERT INTO questions(pageID,file,url,answer) VALUES (?, ?, ?, ?)", { "I:" + ID , "S:" + file , "S:" + url, "S:" + answer });
}

std::vector<std::vector<std::string>> Question::get_question_ID(std::string file){
    return database->Get("SELECT id FROM questions WHERE file=?", { "S:" + file}, 1);
}

void Question::delete_question(size_t question_ID){
    std::string ID = std::to_string(question_ID);
    database->Delete("DELETE FROM questions WHERE id=?", { "I:" + ID});
}

std::vector<std::vector<std::string>> Question::get_all_question_info(size_t question_ID){
    std::string ID = std::to_string(question_ID);
    return database->Get("SELECT * FROM questions WHERE id=?", { "I:" + ID}, 9);
}

std::vector<std::vector<std::string>> Question::get_all_page_questions(size_t page_ID){
    std::string ID = std::to_string(page_ID);
    return database->Get("SELECT * FROM questions WHERE pageID=?", { "I:" + ID}, 9);
}

std::vector<std::vector<std::string>> Question::get_page_ID(size_t question_ID){
    std::string ID = std::to_string(question_ID);
    return database->Get("SELECT pageID FROM questions WHERE id=?", { "I:" + ID}, 1);
}

std::vector<std::vector<std::string>> Question::get_question_file(size_t question_ID){
    std::string ID = std::to_string(question_ID);
    return database->Get("SELECT file FROM questions WHERE id=?", { "I:" + ID}, 1);
}

void Question::update_question_file(size_t question_ID, std::string new_file ){
    std::string ID = std::to_string(question_ID);
    database->Update("UPDATE questions SET file=? WHERE id=?", { "S:" + new_file, "I:" + ID});
}

void Question::update_question_answer(size_t question_ID, std::string new_answer){
    std::string ID = std::to_string(question_ID);
    database->Update("UPDATE questions SET answer=? WHERE id=?", { "S:" + new_answer, "I:" + ID});
}

std::vector<std::vector<std::string>> Question::get_question_answer(size_t question_ID){
    std::string ID = std::to_string(question_ID);
    return database->Get("SELECT answer FROM questions WHERE id=?", { "I:" + ID}, 1);
}

void Question::set_right_answer(size_t question_ID){
    std::string ID = std::to_string(question_ID);
    database->Execute("UPDATE questions SET rightAnswers=(rightAnswers + 1) WHERE id=" + ID);
}

std::vector<std::vector<std::string>> Question::get_right_answers(size_t question_ID){
    std::string ID = std::to_string(question_ID);
    return database->Get("SELECT rightAnswers FROM questions WHERE id=?", { "I:" + ID}, 1);
}

void Question::set_wrong_answer(size_t question_ID){
    std::string ID = std::to_string(question_ID);
    database->Execute("UPDATE questions SET wrongAnswers=(wrongAnswers + 1) WHERE id=" + ID);
}

std::vector<std::vector<std::string>> Question::get_wrong_answers(size_t question_ID){
    std::string ID = std::to_string(question_ID);
    return database->Get("SELECT wrongAnswers FROM questions WHERE id=?", { "I:" + ID}, 1);
}

std::vector<std::vector<std::string>> Question::get_right_answers_rate(size_t question_ID){
    std::string ID = std::to_string(question_ID);
    return database->Get("SELECT (rigtAnswers / (wrongAnswers + rightAnswers)) FROM questions WHERE id=?", { "I:" + ID}, 1);
}

