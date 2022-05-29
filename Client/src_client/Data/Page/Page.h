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
    Page(const User &user, const std::string &_id);
//    void clear_page(){page_id = "";title = ""; theme = ""; login = ""; created_time = ""; updated_time = ""; last_visited_time = ""; text = ""; questions_id.clear();};
    std::string get_page_id(){ return page_id;}
    int get_user_id(){return user_id;}
    std::string get_title(){ return title;}
    std::string get_theme(){return theme;}
    std::string get_login(){return login;}
    std::string get_created_time(){return created_time;}
    std::string  get_updated_time(){return updated_time;}
    std::string  get_last_visited_time(){return last_visited_time;}
    std::string get_text(){return text;}
    std::vector<unsigned int> get_questions_id(){return questions_id;}

    void set_page_id(const std::string &new_id){page_id = new_id;}
    void set_user_id(const int & new_user_id){user_id = new_user_id;}
    void set_title(const std::string & new_title){title = new_title;}
    void set_theme(const std::string & new_theme){theme = new_theme;}
    void set_login(const std::string & new_login){login = new_login;}
    void set_created_time(const std::string & new_created_time){created_time = new_created_time;}
    void set_updated_time(const std::string & new_updated_time){updated_time = new_updated_time;}
    void set_last_visited_time(const std::string & new_last_visited_time){last_visited_time = new_last_visited_time;}
    void set_text(const std::string & new_text){text = new_text;}
    void set_questions_id(const std::vector<unsigned int> new_questions_id){questions_id = new_questions_id;}
private:
    std::string page_id;
    int user_id;
    std::string title;
    std::string theme;
    std::string login;
    std::string created_time;
    std::string  updated_time;
    std::string  last_visited_time;
    std::string text;
    std::vector<unsigned int> questions_id;
};
std::string current_time();
#endif //CLIENT_NOTE_H
