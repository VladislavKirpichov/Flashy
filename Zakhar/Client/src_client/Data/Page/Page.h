#ifndef CLIENT_NOTE_H
#define CLIENT_NOTE_H

#include<vector>
#include <ctime>
#include <string>
#include "Question.h"
#include "User.h"
class Page{
public:
    Page();
    Page(const User &user, const unsigned int &_id);

private:
    unsigned int id;
    std::string title;
    std::string author_login;
    std::string created_time;
    std::string  updated_time;
    std::string  last_visited_time;
    std::string text;
    std::vector<unsigned int> questions_id;
};
std::string current_time();
#endif //CLIENT_NOTE_H
