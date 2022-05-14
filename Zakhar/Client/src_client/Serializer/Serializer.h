

#ifndef CLIENT_SERIALIZER_H
#define CLIENT_SERIALIZER_H
#include<string>
#include<vector>
#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/json_parser.hpp>
#include "User.h"
class Serializer{
public:
    User user_deserialize(std::string);
    std::string user_serialize(const User & user);
private:

};
#endif //CLIENT_SERIALIZER_H
