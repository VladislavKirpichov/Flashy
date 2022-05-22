#include "DB.h"
#include "DB_tables_users.h"
#include "DB_tables_page.h"
#include "DB_tables_question.h"
#include <iostream>
#include <vector>

int main() {

    std::vector<std::vector<std::string>> MyData;

    DB *database = new DB("LAPTOP-9KQ1QFS1.local", "3306", "Admin", "123", "flashy");

    MyData = database->Get("SELECT * FROM users WHERE id=?", {"I:4"}, 5);

    database->Close();

    for (int a = 0; a < MyData.size(); a++) {
        for (int c = 0; c < MyData[a].size(); c++) {
            std::cout << MyData[a][c] + " - ";
        } std::cout << " " << std::endl;
    }

    /*
    std::vector<std::vector<std::string>> MyData;
    User user("Fred");
    user.user_connect_DB();
    //user.user_close_connect();

    //user.add_user();
    int test = user.get_user_ID_by_nick();
    user.user_close_connect();

    //std::string test = MyData[0][0];
    std::cout << test << std::endl;
    
    DB *database = new DB("LAPTOP-9KQ1QFS1.local", "3306", "Admin", "123", "flashy");

    std::string nick = "Alex";
    std::string pass = "Alex123";
    std::string email = "alex@mail.ru";
    std::string status = "student";
    //size_t id = 3;

    //database->delete_user(11);
    
    database->add_user(nick, pass, email, status);

    MyData = database->get_all_user_info(12);

    database->Close();
    
    
    for (int a = 0; a < MyData.size(); a++) {
        for (int c = 0; c < MyData[a].size(); c++) {
            std::cout << MyData[a][c] + " - ";
        } std::cout << " " << std::endl;
    }
    */

   
}