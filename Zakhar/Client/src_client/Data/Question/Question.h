
#ifndef CLIENT_QUESTION_H
#define CLIENT_QUESTION_H
#include<string>
#include<vector>
class Question{
public:

private:
    std::string question;
    std::vector<std::string> answer;
    unsigned int right_answer;
};
#endif //CLIENT_QUESTION_H
