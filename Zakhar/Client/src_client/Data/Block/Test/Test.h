
#ifndef CLIENT_TEST_H
#define CLIENT_TEST_H
#include"Block.h"
#include<string>
#include<vector>
class Test: public Block{
public:

private:
    std::string question;
    std::vector<std::string> answer;
    unsigned int right_answer;
};
#endif //CLIENT_TEST_H
