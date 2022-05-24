//
// Created by vladislav on 19.05.22.
//

#ifndef SERVER_V0_1_JSONSERIALIZER_HPP
#define SERVER_V0_1_JSONSERIALIZER_HPP

#include <vector>
#include <string>
#include <tuple>
#include "User.h"
#include "Page.h"
#include "Question.h"


class JsonSerializer {
public:
    static std::string serialize_user(const User& user);
    static User deserialize_user(const std::string& input_data);

    static std::string serialize_page(const Page& user);
    static Page deserialize_page(const std::string& input_data);

    static std::string serialize_question(const Question& user);
    static Question deserialize_question(const std::string& input_data);

    static std::string serialize(const std::vector<std::vector<std::string>>& input_data);
    static std::string serialize(const std::vector<std::tuple<std::string , std::string>>& input_data);
    static std::vector<std::vector<std::string>> deserialize(const std::string& json_str);

    JsonSerializer() = delete;
    ~JsonSerializer() = delete;
    JsonSerializer(JsonSerializer& json_serializer) = delete;
    JsonSerializer& operator=(JsonSerializer& json_serializer) = delete;
};


#endif //SERVER_V0_1_JSONSERIALIZER_HPP
