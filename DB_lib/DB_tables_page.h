#ifndef DB_tables_page_H_
#define DB_tables_page_H_
#include "DB.h"
#include <string>
#include <vector>

class Page {
    private:
        int id;
        int user_id;
        std::string theme;
        std::string title;
        std::string created_time;
        std::string updated_time;
        std::string last_visited_time;
        std::string file;
        std::vector<std::vector<std::string>> recommend_questions_id;
        DB *database;

    public:

        Page(int user_ID, std::string theme, std::string title, std::string file);

        Page(std::string file);

        void page_connect_DB();

        void page_close_connect();

        void add_page();

		int get_page_ID() const;

        std::vector<std::vector<std::string>> get_all_page_info(size_t page_ID) const;

        std::vector<std::vector<std::string>> get_all_user_pages_id() const;
        
        int get_user_ID() const;

        std::string get_theme() const;

        void update_theme(std::string new_theme);

		void update_page_title(std::string new_title);

		std::string get_page_title() const;

        std::string get_created_time() const;

		void set_updated_time();

		std::string get_updated_time() const;

		void set_last_visited_time();

		std::string get_last_visited_time() const;

		void update_file_page(std::string new_file);

		std::string get_file_page() const;

        std::vector<std::vector<std::string>> get_all_page_questions_id() const;

        std::vector<std::vector<std::string>> get_rec_questions_id() const;

        void add_rec_question_id(std::string q_id);
        void add_one_rec_question_id(std::string q_id);
        void add_five_rec_questions_id(std::vector<std::vector<std::string>> q_id);
        void add_five_rec_questions_id(std::vector<std::string> q_id);

        void set_rec_question_mark(std::string q_id, std::string mark);
        std::string get_rec_question_mark(std::string q_id);
        std::vector<std::vector<std::string>> get_all_rec_question_marks_and_id();

        void delete_page();

};

#endif  // DB_tables_page_H_