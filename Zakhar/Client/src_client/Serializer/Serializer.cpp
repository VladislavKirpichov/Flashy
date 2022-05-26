#include "Serializer.h"

User Serializer::user_deserialize(std::string json) {
    User temp;
    std::stringstream jsonEncoded(json);
    boost::property_tree::ptree root;
    boost::property_tree::read_json(jsonEncoded, root);
    temp.set_name(root.get<std::string>("name" , "ERROR_NAME"));
    temp.set_login(root.get<std::string>("login", "ERROR_LOGIN"));
    temp.set_password(root.get<std::string>("password","ERROR_PASSWORD"));
    temp.set_email(root.get<std::string>("email", "ERROR_EMAIL"));
    temp.set_status(root.get<std::string>("status","ERROR_STATUS"));


    std::vector<unsigned int> pages_id;
    for (boost::property_tree::ptree::value_type &note_id: root.get_child("pages_id")) {
        pages_id.push_back(note_id.second.get_value<unsigned int>());
    }
    temp.set_pages_id(pages_id);

    std::vector<std::string> pages_title;
    for (boost::property_tree::ptree::value_type &note_name: root.get_child("pages_title")) {
        pages_title.push_back(note_name.second.get_value<std::string>());
    }
    temp.set_pages_title(pages_title);

    return temp;
}

std::string Serializer::user_serialize(User &user) {
    std::string res = "{\n";

    res += "  \"name\": \"";
    res += user.get_name();
    res += "\",\n";

    res += "  \"login\": \"";
    res += user.get_login();
    res += "\",\n";

    res += "  \"password\": \"";
    res += user.get_password();
    res += "\",\n";

    res += " \"email\": \"";
    res += user.get_email();
    res += "\",\n";

    res += "  \"status\": \"";
    res += user.get_status();
    res += "\",\n";

    std::vector<unsigned int> temp_pages_id = user.get_pages_id();
    res += "  \"pages_id\": [ ";
    for(size_t i = 0; i < temp_pages_id.size(); i++){
        res+= "\"";
        res+= std::to_string(temp_pages_id[i]);
        res+= "\"";
        if(i<temp_pages_id.size()-1)
            res+= ", ";
    }
    res += "],\n";

    std::vector<std::string> temp_pages_title = user.get_pages_title();
    res += "  \"pages_title\": [ ";
    for(size_t i = 0; i < temp_pages_title.size(); i++){
        res+= "\"";
        res+= temp_pages_title[i];
        res+= "\"";
        if(i<temp_pages_title.size()-1)
            res+= ", ";
    }


    res += "]\n";

    res += "}";
    return res;
}