
#ifndef CLIENT_QUESTION_H
#define CLIENT_QUESTION_H
#include<string>
#include<vector>
class Question{
public:
    Question(): question_id(0), mark(0), title("Input your question"), answer("Input your answer"){}
    Question(const int& _page_id ): question_id(0), mark(0), page_id(_page_id), title("Input your question"), answer("Input your answer"){}
    int get_question_id(){return question_id;}
    int get_page_id(){return page_id;}
    std::string get_title(){return title;}
    std::string get_answer(){return answer;}
    bool is_liked(){return mark==1;}
    void set_question_id(const int &new_id){question_id = new_id;}
    void set_page_id(const int &new_page_id){page_id = new_page_id;}
    void set_title(const std::string &new_title){title = new_title;}
    void set_answer(const std::string &new_answer){answer = new_answer;}
    void set_mark(const int &new_mark){mark = new_mark;}
private:
    int question_id;
    int page_id;
    std::string title;
    std::string answer;
    int mark;

};
#endif //CLIENT_QUESTION_H
