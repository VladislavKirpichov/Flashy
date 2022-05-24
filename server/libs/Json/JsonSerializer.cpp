//
// Created by vladislav on 19.05.22.
//

#include "JsonSerializer.h"
#include "nlohmann/json.hpp"
#include "Exceptions.h"
#include <iostream>


std::string JsonSerializer::serialize(const std::vector<std::vector<std::string>>& input_data) {
    try {
        nlohmann::json json_data{};
        std::vector<std::string>::const_iterator value_it{};

        for (auto &field: input_data) {
            value_it = field.begin() + 1;
            if (field.size() == 2)
                json_data[*field.begin()] = *value_it;
            else
                for (; value_it != field.end(); ++value_it)
                    json_data[*field.begin()] += *value_it;
        }

        return to_string(json_data);
    }
    // TODO: написать обработчики ошибок
    // https://json.nlohmann.me/home/exceptions/
    catch (nlohmann::json::exception& ec) {
        throw JsonException::JsonException(ec);
    }
    catch (...) {
        throw JsonException::JsonException("Some Json error");
    }
}

std::string JsonSerializer::serialize(const std::vector<std::tuple<std::string, std::string>>& input_data) {
    try {
        nlohmann::json json_data{};
        std::vector<std::string>::const_iterator value_it{};

        for (auto &field: input_data)
            json_data[std::get<0>(field)] = std::basic_string(std::get<1>(field));

        return to_string(json_data);
    }
    // TODO: написать обработчики ошибок
    catch (nlohmann::json::exception& ec) {
        throw JsonException::JsonException(ec);
    }
    catch (...) {
        throw JsonException::JsonException("Some Json error");
    }
}

std::vector<std::vector<std::string>> JsonSerializer::deserialize(const std::string& json_str) {
    try {
        nlohmann::json json_data = nlohmann::json::parse(json_str);
        std::vector<std::vector<std::string>> data{};

        for (auto &[key, value]: json_data.items()) {
            data.push_back(std::vector<std::string>{key, value});
        }

        return data;
    }
    // TODO: написать обработчики ошибок
    catch (nlohmann::json::exception& ec) {
        throw JsonException::JsonException(ec);
    }
    catch (...) {
        throw JsonException::JsonException("Some Json error");
    }
}

std::string JsonSerializer::serialize_user(const User &user) {
    try {
        nlohmann::json json_data{};
        json_data["id"] = user.get_id();
        json_data["login"] = user.get_login();
        json_data["password"] = user.get_password();
        json_data["email"] = user.get_email();
        json_data["status"] = user.get_status();

        return to_string(json_data);
    }
    catch (nlohmann::json::exception& ec) {
        throw JsonException::JsonException(ec);
    }
    catch (...) {
        throw JsonException::JsonException("Some Json error");
    }
}

User JsonSerializer::deserialize_user(const std::string &input_data) {
    return {};
}

std::string JsonSerializer::serialize_page(const Page &user) {
    try {
        nlohmann::json json_data{};
        json_data["id"] = user.get_id();
        json_data["login"] = user.get_login();
        json_data["title"] = user.get_title();
        json_data["created_time"] = user.get_created_time();
        json_data["updated_time"] = user.get_updated_time();
        json_data["last_visited_time"] = user.get_last_visited_time();
        json_data["file"] = user.get_file();
        json_data["mime"] = user.get_mime();
        json_data["url"] = user.get_url();

        return to_string(json_data);
    }
    catch (nlohmann::json::exception& ec) {
        throw JsonException::JsonException(ec);
    }
    catch (...) {
        throw JsonException::JsonException("Some Json error");
    }
}

Page JsonSerializer::deserialize_page(const std::string &input_data) {
    return {};
}

std::string JsonSerializer::serialize_question(const Question &user) {
    try {
        nlohmann::json json_data{};
        json_data["id"] = user.get_id();
        json_data["page_id"] = user.get_page_id();
        json_data["file"] = user.get_file();
        json_data["url"] = user.get_url();
        json_data["answer"] = user.get_answer();
        json_data["right_answers"] = user.get_right_answers();
        json_data["wrong_answers"] = user.get_wrong_answers();
        json_data["right_answers_rate"] = user.get_right_answers_rate();

        return to_string(json_data);
    }
    catch (nlohmann::json::exception& ec) {
        throw JsonException::JsonException(ec);
    }
    catch (...) {
        throw JsonException::JsonException("Some Json error");
    }
}

Question JsonSerializer::deserialize_question(const std::string &input_data) {
    return {};
}
/*
template<typename... Args>
std::string JsonSerializer::serialize_any(std::vector<std::tuple<std::string, Args...>> args) {
    try {
        nlohmann::json json_data{};
        std::vector<std::string> temp{};

        for (auto &field : args) {
            temp = std::apply(add_data_to_json, field[1]);
            if (temp.size() == 1)
                json_data[field[0]] = temp[0];
            else {
                for (auto& i : temp)
                    json_data[field[0]] += i;
            }
        }

        return to_string(json_data);
    }
    catch (nlohmann::json::exception& ec) {
        throw JsonException::JsonException(ec);
    }
    catch (...) {
        throw JsonException::JsonException("Some Json error");
    }
}

template<typename... Args>
std::vector<std::string> JsonSerializer::add_data_to_json(Args const&... args) {
    std::vector<std::string> temp;

    (temp.push_back(std::to_string(args)), ...);

    return temp;
}

*/