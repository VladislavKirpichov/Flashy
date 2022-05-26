

#ifndef CLIENT_SERIALIZER_H
#define CLIENT_SERIALIZER_H
#include<string>
#include<vector>
#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/json_parser.hpp>
#include "User.h"
#include "Page.h"
class Serializer{
public:
    User user_deserialize(std::string);
    std::string user_serialize(User & user);
    Page page_deserialize(std::string);
    std::string page_serialize(Page & page);
private:

};
#endif //CLIENT_SERIALIZER_H
