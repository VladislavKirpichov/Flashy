#include "Serializer.h"

User Serializer::user_deserialize(std::string json) {
    User temp;
    std::stringstream jsonEncoded(json);
    boost::property_tree::ptree root;
    boost::property_tree::read_json(jsonEncoded, root);
    temp.set_name(root.get<std::string>("name"));
    temp.set_login(root.get<std::string>("login"));
    temp.set_email(root.get<std::string>("email"));
    temp.set_password(root.get<std::string>("password"));
    temp.set_status(root.get<std::string>("status"));


    std::vector<unsigned int> notes_id;
    for (boost::property_tree::ptree::value_type &note_id: root.get_child("notes_id")) {
        notes_id.push_back(note_id.second.get_value<unsigned int>());
    }
    temp.set_notes_id(notes_id);

    std::vector<std::string> notes_name;
    for (boost::property_tree::ptree::value_type &note_name: root.get_child("notes_name")) {
        notes_name.push_back(note_name.second.get_value<std::string>());
    }
    temp.set_notes_name(notes_name);

    return temp;
}

std::string Serializer::user_serialize(User &user) {
    std::string jsonka = "{\n"
                         "  \"name\": \"Boris\",\n"
                         "  \"login\": \"Boris17\",\n"
                         "  \"email\": \"137\",\n"
                         "  \"password\": \"Demon123\",\n"
                         "  \"status\": \"Student\",\n"
                         "  \"notes_id\": [ \"12\", \"17\"],\n"
                         "  \"notes_name\": [\"Example 1\", \"Example 2\"]\n"
                         "}";
    std::string res = "{\n";

    res += "  \"name\": \"";
    res += user.get_name();
    res += "\",\n";

    res += "  \"login\": \"";
    res += user.get_login();
    res += "\",\n";

    res += " \"email\": \"";
    res += user.get_email();
    res += "\",\n";

    res += "  \"password\": \"";
    res += user.get_password();
    res += "\",\n";

    res += "  \"status\": \"";
    res += user.get_status();
    res += "\",\n";

    std::vector<unsigned int> temp_notes_id = user.get_notes_id();
    res += "  \"notes_id\": [ ";
    for(size_t i = 0; i < temp_notes_id.size(); i++){
        res+= "\"";
        res+= std::to_string(temp_notes_id[i]);
        res+= "\"";
        if(i<temp_notes_id.size()-1)
            res+= ", ";
    }
    res += "],\n";

    std::vector<std::string> temp_notes_name = user.get_notes_name();
    res += "  \"notes_name\": [ ";
    for(size_t i = 0; i < temp_notes_name.size(); i++){
        res+= "\"";
        res+= temp_notes_name[i];
        res+= "\"";
        if(i<temp_notes_name.size()-1)
            res+= ", ";
    }


    res += "]\n";

    res += "}";
    return res;
}