#ifndef DB_TABLES_QUESTIONS_H_
#define DB_TABLES_QUESTIONS_H_
#include "DB.h"
#include <string>
#include <vector>

class Question {
    private:
        int id;
        int page_id;
        std::string file;
        std::string url;
        std::string answer;
        int right_answers;
        int wrong_answers;
        double right_answers_rate;
		DB *database;

    public:
		
		Question(int page_ID, std::string file, std::string url, std::string answer);

		Question(std::string file);

		void question_connect_DB();

        void question_close_connect();

        void add_question();

		int get_question_ID();

		void delete_question();

		std::vector<std::vector<std::string>> get_all_question_info(size_t question_ID);

		std::vector<std::vector<std::string>> get_all_page_questions_id();

		int get_page_ID();

		void update_question_file(std::string new_file);

		std::string get_question_file();

		void update_question_url(std::string new_url);

		std::string get_question_url();

		void update_question_answer(std::string new_answer);

		std::string get_question_answer();

		void set_right_answer();

		int get_right_answers_count();

		void set_wrong_answer();

		int get_wrong_answers();

		double get_right_answers_rate();

};

#endif  //  DB_TABLES_QUESTIONS_H_