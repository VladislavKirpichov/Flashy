#include "DB.h"
#include "DB_tables_users.h"
#include "DB_tables_page.h"
#include "DB_tables_question.h"
#include <iostream>
#include <vector>

int main() {
    std::vector<std::vector<std::string>> MyData;
    User user;
    user.user_connect_DB();

    user.update_status(12, "worker");
    user.user_close_connect();
    /*
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