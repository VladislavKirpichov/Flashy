#include "DB.h"
#include "DB_tables_users.h"
#include "DB_tables_page.h"
#include "DB_tables_question.h"
#include <iostream>
#include <vector>

int main() {


    bool res = User::find_user_nick("Akim");
    

    std::cout << res << std::endl;




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