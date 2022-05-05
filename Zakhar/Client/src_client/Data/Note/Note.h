#ifndef CLIENT_NOTE_H
#define CLIENT_NOTE_H

#include<vector>
#include <ctime>
#include <string>
#include"Block.h"
class Note{
public:
    Note();
    Note(unsigned int user);
    void add_block(std::string type);

private:
    std::string name;
    std::vector<Block*> blocks;
    unsigned int note_id;
    unsigned int user_id;
    time_t date_of_creation;
    time_t last_seen;
};

#endif //CLIENT_NOTE_H
