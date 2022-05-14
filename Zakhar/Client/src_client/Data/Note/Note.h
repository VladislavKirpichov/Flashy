#ifndef CLIENT_NOTE_H
#define CLIENT_NOTE_H

#include<vector>
#include <ctime>
#include <string>
#include "Test.h"
#include "Text_field.h"
class Note{
public:
    Note();
    Note(unsigned int user);

private:
    std::string name;
    TextField text;
    Test test;
    unsigned int note_id;
    unsigned int user_id;
    time_t date_of_creation;
    time_t last_seen;
};

#endif //CLIENT_NOTE_H
