#ifndef DB_LIB_DB_H_
#define DB_LIB_DB_H_

#include <vector>
#include <string>
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>


class DB {
protected:
    sql::Driver            *driver;
    sql::Connection        *con;
    sql::Statement         *stmt;
    sql::ResultSet         *res;
    sql::PreparedStatement *prep_stmt;

private:
    void Execute_Query(std::string,
                       std::vector<std::string>);

public:

    DB(std::string, std::string,
       std::string, std::string, std::string);

    DB();

    void Execute(std::string);

    std::vector<std::vector<std::string>>
    Execute(std::string, int);

    void Close();

    void Connect(std::string, std::string,
                 std::string, std::string);

    void Insert(std::string, std::vector<std::string>);

    std::vector<std::vector<std::string>>
    Get(std::string, std::vector<std::string>, int);

    std::vector<std::vector<std::string>>
    Get(std::string, int);

    void Update(std::string, std::vector<std::string>);

    void Delete(std::string, std::vector<std::string>);


    //  User functions

    void add_user(std::string nick, std::string pass, std::string email, std::string status);

    std::vector<std::vector<std::string>> get_user_ID(std::string nick);

    std::vector<std::vector<std::string>> get_all_user_info(size_t user_ID);

    void delete_user(size_t user_ID);

    std::vector<std::vector<std::string>> get_nick(size_t user_ID);

    void update_nick(size_t user_ID, std::string new_nick);

    std::vector<std::vector<std::string>> get_pass(size_t user_ID);

    void update_pass(size_t user_ID, std::string new_pass);

    std::vector<std::vector<std::string>> get_email(size_t user_ID);

    void update_email(size_t user_ID, std::string new_email);

    std::vector<std::vector<std::string>> get_status(size_t user_ID);

    void update_status(size_t user_ID, std::string new_status);


    //  Page functions

    void add_page(size_t user_ID, std::string title, std::string file, std::string mime, std::string url);

    std::vector<std::vector<std::string>> get_page_ID(std::string page_title);

    std::vector<std::vector<std::string>> get_all_page_info(size_t page_ID);

    std::vector<std::vector<std::string>> get_all_user_pages(size_t user_ID);

    std::vector<std::vector<std::string>> get_user_ID(size_t page_ID);

    void update_page_title(size_t page_ID, std::string new_title);

    std::vector<std::vector<std::string>> get_page_title(size_t page_ID);

    std::vector<std::vector<std::string>> get_created_time(size_t page_ID);

    void set_updated_time(size_t page_ID);

    std::vector<std::vector<std::string>> get_updated_time(size_t page_ID);

    void set_last_visited_time(size_t page_ID);

    std::vector<std::vector<std::string>> get_last_visited_time(size_t page_ID);

    void update_file_page(size_t page_ID, std::string new_file);

    std::vector<std::vector<std::string>> get_file_page(size_t page_ID);

    void update_page_mime(size_t page_ID, std::string new_mime);

    std::vector<std::vector<std::string>> get_page_mime(size_t page_ID);

    void update_page_url(size_t page_ID, std::string new_url);

    std::vector<std::vector<std::string>> get_page_url(size_t page_ID);

    void delete_page(size_t page_ID);


    //  Question functions

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

};


#endif  // UTILS_LIB_UTILS_H_