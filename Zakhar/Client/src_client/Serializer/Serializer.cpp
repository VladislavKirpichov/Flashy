#include "Serializer.h"

User Serializer::user_deserialize(const std::string &json) {
    User temp;
    std::stringstream jsonEncoded(json);
    boost::property_tree::ptree root;
    boost::property_tree::read_json(jsonEncoded, root);
    temp.set_name(root.get<std::string>("name" , "ERROR_NAME"));
    temp.set_login(root.get<std::string>("login", "ERROR_LOGIN"));
    temp.set_password(root.get<std::string>("password","ERROR_PASSWORD"));
    temp.set_email(root.get<std::string>("email", "ERROR_EMAIL"));
    temp.set_status(root.get<std::string>("status","ERROR_STATUS"));


    std::vector<std::string> pages_id;
    for (boost::property_tree::ptree::value_type &page_id: root.get_child("pages_id")) {
        pages_id.push_back(page_id.second.get_value<std::string>());
    }
    temp.set_pages_id(pages_id);

    std::vector<std::string> pages_title;
    for (boost::property_tree::ptree::value_type &page_title: root.get_child("pages_title")) {
        pages_title.push_back(page_title.second.get_value<std::string>());
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

    std::vector<std::string> temp_pages_id = user.get_pages_id();
    res += "  \"pages_id\": [ ";
    for(size_t i = 0; i < temp_pages_id.size(); i++){
        res+= "\"";
        res+= temp_pages_id[i];
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
Page Serializer::page_deserialize(const std::string &json){
    Page temp;
    std::stringstream jsonEncoded(json);
    boost::property_tree::ptree root;
    boost::property_tree::read_json(jsonEncoded, root);
    temp.set_page_id(root.get<std::string>("page_id", "ERROR_ID"));
    temp.set_title(root.get<std::string>("title" , "ERROR_TITLE"));
    temp.set_theme(root.get<std::string>("theme", "ERROR_THEME"));
    temp.set_login(root.get<std::string>("login","ERROR_LORIN"));
    temp.set_created_time(root.get<std::string>("created_time", "ERROR_TIME"));
    temp.set_updated_time(root.get<std::string>("updated_time", "ERROR_TIME"));
    temp.set_last_visited_time(root.get<std::string>("last_visited_time","ERROR_TIME"));
    temp.set_text(root.get<std::string>("text","ERROR_TEXT"));

    std::vector<unsigned int> questions_id;
    for (boost::property_tree::ptree::value_type &question_id: root.get_child("questions_id")) {
        questions_id.push_back(question_id.second.get_value<unsigned int>());
    }
    temp.set_questions_id(questions_id);
    return temp;
}
std::string Serializer::page_serialize(Page & page){
    std::string res = "{\n";

    res += "  \"page_id\": \"";
    res += page.get_page_id();
    res += "\",\n";

    res += "  \"title\": \"";
    res += page.get_title();
    res += "\",\n";

    res += " \"theme\": \"";
    res += page.get_theme();
    res += "\",\n";

    res += "  \"login\": \"";
    res += page.get_login();
    res += "\",\n";

    res += "  \"created_time\": \"";
    res += page.get_created_time();
    res += "\",\n";

    res += "  \"updated_time\": \"";
    res += page.get_updated_time();
    res += "\",\n";

    res += "  \"last_visited_time\": \"";
    res += page.get_last_visited_time();
    res += "\",\n";

    res += "  \"text\": \"";
    res += page.get_text();
    res += "\",\n";

    std::vector<unsigned int> temp_questions_id = page.get_questions_id();
    res += "  \"questions_id\": [ ";
    for(size_t i = 0; i < temp_questions_id.size(); i++){
        res+= "\"";
        res+= std::to_string(temp_questions_id[i]);
        res+= "\"";
        if(i<temp_questions_id.size()-1)
            res+= ", ";
    }
    res += "],\n";


    res += "}";
    return res;
}