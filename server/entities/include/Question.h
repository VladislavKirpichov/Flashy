//
// Created by vladislav on 24.05.22.
//

#ifndef SERVER_V0_1_QUESTION_H
#define SERVER_V0_1_QUESTION_H

#include <string>
#include <vector>

class Question {
public:

    void page_connect_DB();

    void page_close_connect();

    void add_question(size_t page_ID, std::string file, std::string url, std::string answer);

    std::vector<std::vector<std::string>> get_question_ID(std::string file);

    void delete_question(size_t question_ID);

    std::vector<std::vector<std::string>> get_all_question_info(size_t question_ID);

    std::vector<std::vector<std::string>> get_all_page_questions(size_t page_ID);

    std::vector<std::vector<std::string>> get_page_ID(size_t question_ID);

    void update_question_file(size_t question_ID, std::string file);

    std::vector<std::vector<std::string>> get_question_file(size_t question_ID);

    void update_question_url(size_t question_ID);

    std::vector<std::vector<std::string>> get_question_url(size_t question_ID);

    void update_question_answer(size_t question_ID, std::string new_answer);

    std::vector<std::vector<std::string>> get_question_answer(size_t question_ID);

    void set_right_answer(size_t question_ID);

    std::vector<std::vector<std::string>> get_right_answers(size_t question_ID);

    void set_wrong_answer(size_t question_ID);

    std::vector<std::vector<std::string>> get_wrong_answers(size_t question_ID);

    std::vector<std::vector<std::string>> get_right_answers_rate(size_t question_ID);

private:
    size_t id;
    size_t page_id;
    std::string file;
    std::string url;
    std::string answer;
    size_t right_answers;
    size_t wrong_answers;
    double right_aswers_rate;
    // DB *database;

};

#endif //SERVER_V0_1_QUESTION_H
