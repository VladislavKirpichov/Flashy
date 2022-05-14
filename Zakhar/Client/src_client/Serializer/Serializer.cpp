#include "Serializer.h"

User Serializer::user_deserialize(std::string json){
    User temp;
    std::stringstream jsonEncoded(json);
    boost::property_tree::ptree root;
    boost::property_tree::read_json(jsonEncoded, root);
    std::cout << root.get<std::string> ("name") << " " << root.get<std::string>("password") << std::endl;
    std::vector<std::string> notes_name;
    for (boost::property_tree::ptree::value_type &note_name : root.get_child("notes_name"))
    {
       // note_name.push_back(note_name.second.get_value<std::string>());
        std::cout << note_name.second.get_value<std::string>() << " ";
    }

    return temp;
}
std::string Serializer::user_serialize(const User & user){
    return "";
}