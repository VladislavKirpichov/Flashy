

#ifndef CLIENT_SERIALIZER_H
#define CLIENT_SERIALIZER_H
#include<string>
#include<vector>
#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/json_parser.hpp>
#include "User.h"
#include "Page.h"
#include "Question.h"
class Serializer{
public:
    User user_deserialize(const std::string &json);
    std::string user_serialize(User & user);
    Page page_deserialize(const std::string &json);
    std::string page_serialize(Page & page);
    Question question_deserialize(const std::string &json);
    std::string question_serialize(Question & question);
};
//std::string user_json_example = "{\n"
//                                "  \"name\": \"moc_name\",\n"
//                                "  \"login\": \"moc_login\",\n"
//                                "  \"password\": \"moc_password\",\n"
//                                "  \"email\": \"moc@example.com\",\n"
//                                "  \"status\": \"Student\",\n"
//                                "  \"pages_id\": [ \"35\", \"358\"],\n"
//                                "  \"pages_title\": [\"Moc Page 1\", \"Moc Page 2\"]\n"
//                                "}";
//
//std::string page_json_example = "{\n"
//                                "  \"id\": \"0\",\n"
//                                "  \"title\": \"moc_title\",\n"
//                                " \"theme\": \"0\",\n"
//                                "  \"login\": \"moc_login\",\n"
//                                "  \"created_time\": \"01:01:1970\",\n"
//                                "  \"updated_time\": \"01:01:1970\",\n"
//                                "  \"last_visited_time\": \"01:01:1970\",\n"
//                                "  \"text\": \"MOC_TEXT MOC_TEXT\",\n"
//                                "  \"questions_id\": [ \"1\", \"2\"]\n"
//                                "}";

//std::string question_json_example = "{\n"
//                                    "  \"title\": \"Moc Question\",\n"
//                                    "  \"answer\": \"Yes\",\n"
//                                    " \"question_id\": \"0\",\n"
//                                    "  \"page_id\": \"\"\n"
//                                    "}";

#endif //CLIENT_SERIALIZER_H
