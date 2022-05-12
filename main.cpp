#include "DB.h"
#include <iostream>
#include <vector>

int main() {
    std::vector<std::vector<std::string>> MyData;
    DB *database = new DB("LAPTOP-9KQ1QFS1.local", "3306", "Admin", "123", "flashy");

    //database->Update("UPDATE Users SET nick=? WHERE id=?", { "S:Bob" , "I:2" });
    std::string nick = "Pete";
    std::string pass = "Pete123";
    std::string email = "pete@mail.ru";
    std::string status = "student";
    size_t id = 5;
    std::string ID = std::to_string(id);
    

    //database->Insert("INSERT INTO users(nick,pass,email,status) VALUES (?, ?, ?, ?)", { "S:" + nick , "S:" + pass , "S:" + email, "S:" + status });

    //database->Update("UPDATE page SET updatedTime=? WHERE id=?", { "S:NOW()" , "I:6" });
    //database->Execute("INSERT INTO page (userID,updatedTime) VALUES ('6', NOW())");
    //database->Execute("UPDATE page SET updatedTime=NOW() WHERE id=6");

    //database->Delete("DELETE FROM Users WHERE id=?", { "I:5" });

    MyData = database->Get("SELECT * FROM users WHERE id=?", {"I:"+ ID}, 5);


    database->Close();

    
    for (int a = 0; a < MyData.size(); a++) {
        for (int c = 0; c < MyData[a].size(); c++) {
            std::cout << MyData[a][c] + " - ";
        } std::cout << " " << std::endl;
    }
    
}