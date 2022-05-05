

#ifndef CLIENT_SERIALIZER_H
#define CLIENT_SERIALIZER_H
#include<string>
#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/json_parser.hpp>
#include "User.h"
class Serializer{
public:
    User user_deserialize(std::string);
private:

};
#endif //CLIENT_SERIALIZER_H
