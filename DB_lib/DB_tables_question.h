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
        std::string answer;
        int right_answers;
        int wrong_answers;
		DB *database;

    public:
		
		Question(int page_ID, std::string file, std::string answer);

		Question(int id);

		void question_connect_DB();

        void question_close_connect();

        void add_question();

		int get_question_ID() const;

		void delete_question();

		std::vector<std::vector<std::string>> get_all_question_info(size_t question_ID) const;

		std::vector<std::vector<std::string>> get_all_page_questions_id() const;

		int get_page_ID() const;

		void update_question_file(std::string new_file);

		std::string get_question_file() const;

		void update_question_answer(std::string new_answer);

		std::string get_question_answer() const;

		void set_right_answer();

		int get_right_answers_count() const;

		void set_wrong_answer();

		int get_wrong_answers() const;

		double get_right_answers_rate() const;

		void set_rec_question_mark(std::string q_id, std::string mark);

		std::string get_rec_question_mark(std::string q_id);

		std::vector<std::vector<std::string>> get_all_rec_question_marks_and_id();

};

#endif  //  DB_TABLES_QUESTIONS_H_