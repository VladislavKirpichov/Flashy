#include "Serializer.h"
User Serializer::user_deserialize(std::string json){
    User temp;
    std::stringstream jsonEncoded(json);
    boost::property_tree::ptree root;
    boost::property_tree::read_json(jsonEncoded, root);

    temp.Change_Name(root.get<std::string> ("name"));
    temp.Change_Password(root.get<std::string>("password"));
    return temp;
}