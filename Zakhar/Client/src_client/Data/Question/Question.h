
#ifndef CLIENT_QUESTION_H
#define CLIENT_QUESTION_H
#include<string>
#include<vector>
class Question{
public:
    unsigned int get_id(){return id;}
    std::string get_page_id(){return page_id;}
    std::string get_title(){return title;}
    std::string get_answer(){return answer;}
    bool is_liked(){return mark==1;}
    void set_id(const unsigned int &new_id){id = new_id;}
    void set_page_id(const std::string &new_page_id){page_id = new_page_id;}
    void set_title(const std::string &new_title){title = new_title;}
    void set_answer(const std::string &new_answer){answer = new_answer;}
    void set_mark(const int &new_mark){mark = new_mark;}
private:
    unsigned int id;
    std::string page_id;
    std::string title;
    std::string answer;
    int mark;

};
#endif //CLIENT_QUESTION_H
