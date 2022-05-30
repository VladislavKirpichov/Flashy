#include <gtest/gtest.h>
#include <vector>
#include "DB.h"
#include "DB_tables_users.h"
#include "DB_tables_page.h"

/*
TEST(DB_tests, Connect_function_Close_connect_function) {
    EXPECT_NO_THROW(DB *database = new DB("LAPTOP-9KQ1QFS1.local", "3306", "Admin", "123", "flashy"));
    //EXPECT_NO_THROW(database->Close());
}


TEST(DB_tests, Delete_function) {
    DB *database = new DB("LAPTOP-9KQ1QFS1.local", "3306", "Admin", "123", "flashy");
    EXPECT_ANY_THROW(database->Delete("DELETE FROM users WHERE id=?", { "I15" }));
    database->Close();
}
*/

TEST(DB_tests, Get_function) {

    DB *database = new DB("LAPTOP-9KQ1QFS1.local", "3306", "Admin", "123", "flashy");

    std::vector<std::vector<std::string>> MyData = database->Get("SELECT id FROM users WHERE nick=?", { "S:Akim" }, 1);

    database->Close();

    EXPECT_EQ(MyData[0][0], "4");
}

TEST(DB_tests, Insert_function) {
    DB *database = new DB("LAPTOP-9KQ1QFS1.local", "3306", "Admin", "123", "flashy");

    database->Insert("INSERT INTO users(nick,name,pass,email,status) VALUES (?, ?, ?, ?, ?)", { "S:Billy" , "S:Bill", "S:bill123" , "S:bill@mail.ru", "S:student"});

    std::vector<std::vector<std::string>> MyData = database->Get("SELECT pass FROM users WHERE nick=?", { "S:Billy"}, 1);

    EXPECT_EQ(MyData[0][0], "bill123");
    database->Delete("DELETE FROM users WHERE nick=?", { "S:Billy" });

    database->Close();
}

TEST(DB_tests, Update_function) {
    DB *database = new DB("LAPTOP-9KQ1QFS1.local", "3306", "Admin", "123", "flashy");

    database->Update("UPDATE users SET name=? WHERE id=?", { "S:Robert" , "I:5" });

    std::vector<std::vector<std::string>> MyData = database->Get("SELECT name FROM users WHERE id=?", { "I:5"}, 1);

    EXPECT_EQ(MyData[0][0], "Robert");

    database->Close();
}


TEST(User_tests, get_user_ID_function) {
    User user("Adam");

    int res = user.get_user_ID();

    EXPECT_EQ(res, 6);
    user.user_close_connect();
}

TEST(User_tests, get_user_nick_function) {
    User user("Adam");

    std::string res = user.get_nick();

    EXPECT_EQ(res, "Adam");
    user.user_close_connect();
}

TEST(User_tests, get_user_name_function) {
    User user("Adam");

    std::string res = user.get_name();

    EXPECT_EQ(res, "Adamas");
    user.user_close_connect();
}

TEST(User_tests, get_user_pass_function) {
    User user("Adam");

    std::string res = user.get_pass();

    EXPECT_EQ(res, "123");
    user.user_close_connect();
}

TEST(User_tests, get_user_email_function) {
    User user("Adam");

    std::string res = user.get_email();

    EXPECT_EQ(res, "adam@mail.ru");
    user.user_close_connect();
}

TEST(User_tests, get_user_status_function) {
    User user("Adam");

    std::string res = user.get_status();

    EXPECT_EQ(res, "student");
    user.user_close_connect();
}

TEST(User_tests, update_user_pass_function) {
    User user("Adam");

    user.update_pass("456");

    std::string res = user.get_pass();

    EXPECT_EQ(res, "456");

    user.update_pass("123");
    user.user_close_connect();
}

TEST(User_tests, find_user_nick_function) {

    EXPECT_TRUE( User::find_user_nick("Alex", "Alex123"));
}

TEST(Page_tests, get_page_id) {
    Page page("sss");
    int res = page.get_page_ID();
    EXPECT_EQ(res, 1);
    page.page_close_connect();
}

TEST(Page_tests, get_user_id) {
    Page page("sss");
    int res = page.get_user_ID();
    EXPECT_EQ(res, 4);
    page.page_close_connect();
}

TEST(Page_tests, get_page_theme) {
    Page page("kkk");
    std::string res = page.get_theme();
    EXPECT_EQ(res, "Math");
    page.page_close_connect();
}

TEST(Page_tests, get_page_title) {
    Page page("5", true);
    page.update_page_title("Linal");
    std::string res = page.get_page_title();
    EXPECT_EQ(res, "Linal");
    page.page_close_connect();
}

TEST(Page_tests, update_page_title) {
    Page page("sss");
    std::string res = page.get_page_title();
    EXPECT_EQ(res, "Диффуры");
    page.page_close_connect();
}

TEST(Page_tests, get_page_file) {
    Page page("sss");
    std::string res = page.get_file_page();
    EXPECT_EQ(res, "sss");
    page.page_close_connect();
}

TEST(Page_tests, get_all_page_questions_id) {
    Page page("sss");
    std::vector<std::vector<std::string>> res = page.get_all_page_questions_id();
    EXPECT_EQ(res[1][0], "2");
    page.page_close_connect();
}

TEST(Page_tests, add_page) {
    Page page(13, "Math", "Тервер", "uuu");
    page.add_page();
    std::string res = page.get_file_page();
    EXPECT_EQ(res, "uuu");
    page.page_close_connect();
}

TEST(Page_tests, add_one_rec_question_id) {
    Page page("uuu");
    page.add_one_rec_question_id("10");
    std::vector<std::vector<std::string>> res = page.get_all_rec_question_marks_and_id();
    EXPECT_EQ(res[0][0], "10");
    page.delete_page();
    page.page_close_connect();
}



















