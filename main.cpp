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
/*
    Page page(7, "Math", "Algos", "kkk");

    page.add_page();

    std::vector<std::string> Ques = {"1", "2", "3", "4", "5"};

    page.add_five_rec_questions_id(Ques);

    std::vector<std::vector<std::string>> MyData = page.get_rec_questions_id();


    page.page_close_connect();

    for (int a = 0; a < MyData.size(); a++) {
        for (int c = 0; c < MyData[a].size(); c++) {
            std::cout << MyData[a][c] + " - ";
        } std::cout << " " << std::endl;
    }

*/
    //User user("Paul", "Paul", "123", "paul@mail.ru", "student");

    //user.add_user();
    //user.user_close_connect();

    DB *database = new DB("LAPTOP-9KQ1QFS1.local", "3306", "Admin", "123", "flashy");
    database->Insert("INSERT INTO users(nick,name,pass,email,status) VALUES (?, ?, ?, ?, ?)", { "S:Paul", "S:Paul" , "S:pass" , "S:email", "S:status"});
    database->Close();
    
    /*
    for (int a = 0; a < MyData.size(); a++) {
        for (int c = 0; c < MyData[a].size(); c++) {
            std::cout << MyData[a][c] + " - ";
        } std::cout << " " << std::endl;
    }
    */

    


   
}