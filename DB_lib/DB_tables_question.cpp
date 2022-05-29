#include "DB.h"
#include "DB_tables_question.h"

Question::Question(int page_ID, std::string file, std::string answer)
    : page_id(page_ID), file(file), answer(answer)
{
    question_connect_DB();
}

Question::Question(int id)
    : id(id)
{
    question_connect_DB();

    //std::vector<std::vector<std::string>> MyData = database->Get("SELECT id FROM questions WHERE file=?", { "S:" + file}, 1);
    //id = std::stoi(MyData[0][0]);
    
    std::string ID = std::to_string(this->id);
    std::vector<std::vector<std::string>> MyData = database->Get("SELECT * FROM questions WHERE id=?", {"I:"+ ID}, 6);

    page_id = std::stoi(MyData[0][1]);
    file = MyData[0][2];
    answer = MyData[0][3];
    right_answers = std::stoi(MyData[0][4]);
    wrong_answers = std::stoi(MyData[0][5]);
    //MyData = database->Get("SELECT `rightAnswers`, `wrongAnswers`, (`rightAnswers` / (`rightAnswers` + `wrongAnswers`)) FROM questions WHERE id=?", { "I:" + ID}, 1);
    //right_answers_rate = std::stod(MyData[0][7]);
    
}

void Question::question_connect_DB() {
    database = new DB("LAPTOP-9KQ1QFS1.local", "3306", "Admin", "123", "flashy");
}

void Question::question_close_connect() {
    database->Close();
}

void Question::add_question(){
    std::string Page_ID = std::to_string(page_id);
    database->Insert("INSERT INTO questions(pageID,file,answer) VALUES (?, ?, ?)", { "I:" + Page_ID , "S:" + file, "S:" + answer });
    std::vector<std::vector<std::string>> MyData = database->Get("SELECT id FROM questions WHERE file=?", { "S:" + file}, 1);
    id = std::stoi(MyData[0][0]);
}

int Question::get_question_ID() const {
    //return database->Get("SELECT id FROM questions WHERE file=?", { "S:" + file}, 1);
    return id;
}

void Question::delete_question(){
    std::string ID = std::to_string(id);
    database->Delete("DELETE FROM questions WHERE id=?", { "I:" + ID});
}

std::vector<std::vector<std::string>> Question::get_all_question_info(size_t question_ID) const{
    std::string ID = std::to_string(question_ID);
    return database->Get("SELECT * FROM questions WHERE id=?", { "I:" + ID}, 9);
}

std::vector<std::vector<std::string>> Question::get_all_page_questions_id() const {
    std::string page_ID = std::to_string(page_id);
    return database->Get("SELECT id FROM questions WHERE pageID=?", { "I:" + page_ID}, 1);
}

int Question::get_page_ID() const{
    //std::string ID = std::to_string(question_ID);
    //return database->Get("SELECT pageID FROM questions WHERE id=?", { "I:" + ID}, 1);
    return page_id;
}

std::string Question::get_question_file() const{
    //std::string ID = std::to_string(question_ID);
    //return database->Get("SELECT file FROM questions WHERE id=?", { "I:" + ID}, 1);
    return file;
}

void Question::update_question_file(std::string new_file ){
    std::string ID = std::to_string(id);
    database->Update("UPDATE questions SET file=? WHERE id=?", { "S:" + new_file, "I:" + ID});
    file = new_file;
}

void Question::update_question_answer(std::string new_answer){
    std::string ID = std::to_string(id);
    database->Update("UPDATE questions SET answer=? WHERE id=?", { "S:" + new_answer, "I:" + ID});
    answer = new_answer;
}

std::string Question::get_question_answer() const{
    //std::string ID = std::to_string(question_ID);
    //return database->Get("SELECT answer FROM questions WHERE id=?", { "I:" + ID}, 1);
    return answer;
}

void Question::set_right_answer(){
    std::string ID = std::to_string(id);
    database->Execute("UPDATE questions SET rightAnswers=(rightAnswers + 1) WHERE id=" + ID);

    right_answers++;

}

int Question::get_right_answers_count()const{
    //std::string ID = std::to_string(question_ID);
    //return database->Get("SELECT rightAnswers FROM questions WHERE id=?", { "I:" + ID}, 1);
    return right_answers;
}

void Question::set_wrong_answer(){
    std::string ID = std::to_string(id);
    database->Execute("UPDATE questions SET wrongAnswers=(wrongAnswers + 1) WHERE id=" + ID);
    wrong_answers++;
}

int Question::get_wrong_answers() const{
    //std::string ID = std::to_string(question_ID);
    //return database->Get("SELECT wrongAnswers FROM questions WHERE id=?", { "I:" + ID}, 1);
    return wrong_answers;
}

double Question::get_right_answers_rate() const{
    //std::string ID = std::to_string(id);
    //return database->Get("SELECT `rightAnswers`, `wrongAnswers`, (`rightAnswers` / (`rightAnswers` + `wrongAnswers`)) FROM questions WHERE id=?", { "I:" + ID}, 1);
    double res =((double)right_answers / (right_answers + wrong_answers));
    return res;
    //return right_answers_rate;
    //SELECT `rightAnswers`, `wrongAnswers`, (`rightAnswers` / (`rightAnswers` + `wrongAnswers`)) AS Rate FROM questions
}

void Question::set_rec_question_mark(std::string page_id, std::string mark) {
    std::string ID = std::to_string(id);
    database->Update("UPDATE recommend_questions SET mark=? WHERE page_ID=? AND rec_question_id=?", { "I:" + mark, "I:" + page_id, "I:" + ID});
}

std::string Question::get_rec_question_mark(std::string page_id) {
    std::string ID = std::to_string(id);
    std::vector<std::vector<std::string>> MyData = database->Get("SELECT mark FROM recommend_questions WHERE page_ID=? AND rec_question_id=?", { "I:" + page_id, "I:" + ID}, 1);
    return MyData[0][0];
}

std::vector<std::vector<std::string>> Question::get_all_rec_question_marks_and_id() {
    std::string page_ID = std::to_string(page_id);
    return database->Get("SELECT rec_question_id, mark FROM recommend_questions WHERE page_ID=?", { "I:" + page_ID}, 2);
}
