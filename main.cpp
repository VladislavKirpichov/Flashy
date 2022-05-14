#include "DB.h"
#include <iostream>
#include <vector>

int main() {
    std::vector<std::vector<std::string>> MyData;
    DB *database = new DB("LAPTOP-9KQ1QFS1.local", "3306", "Admin", "123", "flashy");

    std::string nick = "Alex";
    std::string pass = "Alex123";
    std::string email = "alex@mail.ru";
    std::string status = "student";
    size_t id = 10;

    database->add_user(nick, pass, email, status);
    MyData = database->get_nick(id);
    database->Close();

    
    for (int a = 0; a < MyData.size(); a++) {
        for (int c = 0; c < MyData[a].size(); c++) {
            std::cout << MyData[a][c] + " - ";
        } std::cout << " " << std::endl;
    }
    
    
}