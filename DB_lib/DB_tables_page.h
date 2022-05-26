#ifndef DB_tables_page_H_
#define DB_tables_page_H_
#include "DB.h"
#include <string>
#include <vector>

class Page {
    private:
        int id;
        int user_id;
        std::string title;
        std::string created_time;
        std::string updated_time;
        std::string last_visited_time;
        std::string file;
        DB *database;

    public:

        Page(int user_ID, std::string title, std::string file);

        Page(std::string file);

        void page_connect_DB();

        void page_close_connect();

        void add_page();

		int get_page_ID();

        std::vector<std::vector<std::string>> get_all_page_info(size_t page_ID);

        std::vector<std::vector<std::string>> get_all_user_pages_id();
        
        int get_user_ID();

		void update_page_title(std::string new_title);

		std::string get_page_title();

        std::string get_created_time();

		void set_updated_time();

		std::string get_updated_time();

		void set_last_visited_time();

		std::string get_last_visited_time();

		void update_file_page(std::string new_file);

		std::string get_file_page();

		//void update_page_mime(size_t page_ID, std::string new_mime);

		//std::vector<std::vector<std::string>> get_page_mime(size_t page_ID);

		//void update_page_url(size_t page_ID, std::string new_url);

		//std::vector<std::vector<std::string>> get_page_url(size_t page_ID);

        void delete_page();

};

#endif  // DB_tables_page_H_