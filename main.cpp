#include "DB.h"
#include "DB_tables_users.h"
#include "DB_tables_page.h"
#include "DB_tables_question.h"
#include <iostream>
#include <vector>

int main() {

    //User user("Bob");
    //user.update_email("new_email");
    //user.user_close_connect();

    Page page("sss");

    page.set_rec_questions_id(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

    std::vector<std::vector<std::string>> MyData = page.get_rec_questions_id();


    page.page_close_connect();

    for (int a = 0; a < MyData.size(); a++) {
        for (int c = 0; c < MyData[a].size(); c++) {
            std::cout << MyData[a][c] + " - ";
        } std::cout << " " << std::endl;
    }





    /*
    std::string nickname = "'Akim'"; 

    DB *database = new DB("LAPTOP-9KQ1QFS1.local", "3306", "Admin", "123", "flashy");
    std::vector<std::vector<std::string>> MyData = database->Execute("SELECT id FROM users WHERE nick = " + nickname, 1);
    database->Close();
    */
    
    /*
    for (int a = 0; a < MyData.size(); a++) {
        for (int c = 0; c < MyData[a].size(); c++) {
            std::cout << MyData[a][c] + " - ";
        } std::cout << " " << std::endl;
    }
    */

    


   
}