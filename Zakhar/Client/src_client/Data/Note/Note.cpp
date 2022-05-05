#include "Note.h"
Note::Note(){
    user_id = 0;
}
Note::Note(unsigned int user){
    date_of_creation = time(NULL);
    last_seen = date_of_creation;
    user_id = user;
    note_id = 0;
}
void Note::add_block(std::string type){

}