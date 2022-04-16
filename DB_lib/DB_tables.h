#ifndef DB_TABLES_H_
#define DB_TABLES_H_

#include "DB.h"
#include <string>

class User : public DB {
    private:
        size_t id;
        std::string nickname;
        std::string password;
        std::string email;
        std::string status;

    public:
        User (std::string, std::string, std::string, std::string);

        size_t getID();

        std::vector<std::vector<std::string>> get_all_user_info();

        void delete_user();

        std::string get_nick();

        void set_nick(std::string);

        void update_nick(std::string);

        std::string get_pass();

        void update_pass(std::string);

        std::string get_email();

        void update_email(std::string);

        std::string get_status();

        void update_status(std::string);
};

class Page : DB {
    private:
        size_t id;

        size_t userID;

        time_t created;

        time_t updated;

        time_t last_visited;
    
    public:

        Page(size_t, time_t, time_t, time_t);
        std::vector<std::vector<std::string>> get_all_page_info();

        size_t getID();
        
        size_t get_userID();

        std::vector<std::vector<std::string>> get_user_pages();

        void delete_page();

        time_t get_created_time();

        time_t get_updated_time();

        void update_updated_time(time_t);

};

class Block : DB {
    private:
        size_t id;

        std::string type;

        size_t pageID;

        size_t size;

        std::string mime;

        size_t file;

        size_t url;

    public:

        Block(std::string, size_t, size_t, std::string, size_t, size_t);
        std::vector<std::vector<std::string>> get_all_block_info();
        void delete_block();
        std::string get_type();
        std::string get_block();
        std::vector<std::vector<std::string>> get_page_blocks();
};

class Question : DB {
    private:
        size_t id;

        size_t blockID;

        std::string file;

        std::string url;

        std::string answer;
    
    public:

        Question(size_t, std::string, std::string, std::string);

        std::string get_question();

        std::string get_answer();

        void update_answer(std::string);
};

#endif  // DB_TABLES_H_