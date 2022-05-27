
// TODO: ПОДКЛЮЧИТЬ БД!

#include "DB.h"

void DB::add_question(size_t page_ID, std::string file, std::string url, std::string answer){
    std::string ID = std::to_string(page_ID);
    Insert("INSERT INTO page(pageID,file,url,answer) VALUES (?, ?, ?, ?)", { "I:" + page_ID , "S:" + file , "S:" + url, "S:" + answer });
}

std::vector<std::vector<std::string>> DB::get_question_ID(std::string file){
    return Get("SELECT id FROM questions WHERE file=?", { "S:" + file}, 1);
}

void DB::delete_question(size_t question_ID){
    std::string ID = std::to_string(question_ID);
    Delete("DELETE FROM questions WHERE id=?", { "I:" + ID});
}

std::vector<std::vector<std::string>> DB::get_all_question_info(size_t question_ID){
    std::string ID = std::to_string(question_ID);
    return Get("SELECT * FROM questions WHERE id=?", { "I:" + ID}, 9);
}

std::vector<std::vector<std::string>> DB::get_all_page_questions(size_t page_ID){
    std::string ID = std::to_string(page_ID);
    return Get("SELECT * FROM questions WHERE pageID=?", { "I:" + ID}, 9);
}

std::vector<std::vector<std::string>> DB::get_page_ID(size_t question_ID){
    std::string ID = std::to_string(question_ID);
    return Get("SELECT pageID FROM questions WHERE id=?", { "I:" + question_ID}, 1);
}

std::vector<std::vector<std::string>> DB::get_question_file(size_t question_ID){
    std::string ID = std::to_string(question_ID);
    return Get("SELECT file FROM questions WHERE id=?", { "I:" + question_ID}, 1);
}

void DB::update_question_file(size_t question_ID, std::string new_file ){
    std::string ID = std::to_string(question_ID);
    Update("UPDATE questions SET file=? WHERE id=?", { "S:" + new_file, "I:" + ID});
}

void DB::update_question_answer(size_t question_ID, std::string new_answer){
    std::string ID = std::to_string(question_ID);
    Update("UPDATE questions SET answer=? WHERE id=?", { "S:" + new_answer, "I:" + ID});
}

std::vector<std::vector<std::string>> DB::get_question_answer(size_t question_ID){
    std::string ID = std::to_string(question_ID);
    return Get("SELECT answer FROM questions WHERE id=?", { "I:" + ID}, 1);
}

void DB::set_right_answer(size_t question_ID){
    std::string ID = std::to_string(question_ID);
    Execute("UPDATE questions SET rightAnswers=(rightAnswers + 1) WHERE id=" + ID);
}

std::vector<std::vector<std::string>> DB::get_right_answers(size_t question_ID){
    std::string ID = std::to_string(question_ID);
    return Get("SELECT rightAnswers FROM questions WHERE id=?", { "I:" + ID}, 1);
}

void DB::set_wrong_answer(size_t question_ID){
    std::string ID = std::to_string(question_ID);
    Execute("UPDATE questions SET wrongAnswers=(wrongAnswers + 1) WHERE id=" + ID);
}

std::vector<std::vector<std::string>> DB::get_wrong_answers(size_t question_ID){
    std::string ID = std::to_string(question_ID);
    return Get("SELECT wrongAnswers FROM questions WHERE id=?", { "I:" + ID}, 1);
}

std::vector<std::vector<std::string>> DB::get_right_answers_rate(size_t question_ID){
    std::string ID = std::to_string(question_ID);
    return Get("SELECT (rigtAnswers / (wrongAnswers + rightAnswers)) FROM questions WHERE id=?", { "I:" + ID}, 1);
}
