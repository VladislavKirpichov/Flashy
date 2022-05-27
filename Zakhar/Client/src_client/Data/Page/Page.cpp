#include "Page.h"

Page::Page() {
    id = 0;
    theme = 0;
}

Page::Page(const User &user, const unsigned int &_id) {
    id = _id;
    theme = 0;
    created_time =  current_time();
    updated_time = created_time;
    last_visited_time = created_time;
    login = user.get_login();

}

std::string current_time() {
    time_t sec = time(NULL);
    tm *ltm = localtime(&sec);
    std::string temp;
    temp += std::to_string(ltm->tm_mday);
    temp += ':';
    if (ltm->tm_mon <= 9)
        temp += '0';
    temp += std::to_string(1 + ltm->tm_mon);
    temp += ':';
    temp += std::to_string(1900 + ltm->tm_year);
    return temp;
}