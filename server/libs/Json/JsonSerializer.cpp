//
// Created by vladislav on 19.05.22.
//

#include "JsonSerializer.h"
#include "nlohmann/json.hpp"
#include "Exceptions.h"
#include "User.h"
#include "Page.h"
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
    catch (nlohmann::json::exception& ec) {
        throw JsonException::JsonException(ec);
    }
    catch (...) {
        throw JsonException::JsonException("Some Json error");
    }
}

std::string JsonSerializer::serialize(const std::unordered_map<std::string, std::string> &input_data) {
    try {
        nlohmann::json json_data{};

        for (auto [key, value]: input_data)
            json_data[key] = value;

        return to_string(json_data);
    }
    catch (nlohmann::json::exception &ec) {
        throw JsonException::JsonException(ec);
    }
    catch (...) {
        throw JsonException::JsonException("Some Json error");
    }
}

std::unordered_map<std::string, std::string> JsonSerializer::deserialize(const std::string& json_str) {
    try {
        nlohmann::json json_data = nlohmann::json::parse(json_str);
        std::unordered_map<std::string, std::string> data{};

        for (auto &[key, value]: json_data.items())
            data[key] = value;

        return data;
    }
    catch (nlohmann::json::exception& ec) {
        throw JsonException::JsonException(ec);
    }
    catch (...) {
        throw JsonException::JsonException("Some Json error");
    }
}

std::unordered_map<std::string, std::vector<std::string>> JsonSerializer::deserialize_in_vector(const std::string& json_str) {
    try {
        nlohmann::json json_data = nlohmann::json::parse(json_str);
        std::unordered_map<std::string, std::vector<std::string>> data{};

        // TODO передалать question id
        for (auto &[key, value]: json_data.items())
            for (auto&i : value)
                data[key].push_back(i);

        return data;
    }
    catch (nlohmann::json::exception& ec) {
        throw JsonException::JsonException(ec);
    }
    catch (...) {
        throw JsonException::JsonException("Some Json error");
    }
}

std::string JsonSerializer::serialize_user(const User& user) {
    try {
        nlohmann::json json_data{};
        json_data["id"] = user.get_user_ID();
        json_data["login"] = user.get_nick();
        json_data["password"] = user.get_pass();
        json_data["email"] = user.get_email();
        json_data["status"] = user.get_status();

        for (auto& i : user.get_pages_file())
            json_data["pages_id"] += i[0];

        for (auto& i : user.get_pages_title())
            json_data["pages_titles"] += i[0];

        return to_string(json_data);
    }
    catch (nlohmann::json::exception& ec) {
        throw JsonException::JsonException(ec);
    }
    catch (...) {
        throw JsonException::JsonException("Some Json error");
    }
}

std::string JsonSerializer::serialize_page(const Page &page) {
    try {
        nlohmann::json json_data{};
        json_data["id"] = page.get_page_ID();
        json_data["login"] = page.get_user_ID();
        json_data["title"] = page.get_page_title();
        json_data["created_time"] = page.get_created_time();
        json_data["updated_time"] = page.get_updated_time();
        json_data["last_visited_time"] = page.get_last_visited_time();
        json_data["page_id"] = page.get_file_page();

        for (auto& i : page.get_all_page_questions_id())
            json_data["questions_id"] += i[0];

        return to_string(json_data);
    }
    catch (nlohmann::json::exception& ec) {
        throw JsonException::JsonException(ec);
    }
    catch (...) {
        throw JsonException::JsonException("Some Json error");
    }
}

std::string JsonSerializer::serialize_question(const Question &question) {
    try {
        nlohmann::json json_data{};
        json_data["id"] = question.get_question_ID();
        json_data["page_id"] = question.get_page_ID();
        json_data["title"] = question.get_question_file();
        json_data["answer"] = question.get_question_answer();
        // json_data["mark"] = question.get_mark();

        return to_string(json_data);
    }
    catch (nlohmann::json::exception& ec) {
        throw JsonException::JsonException(ec);
    }
    catch (...) {
        throw JsonException::JsonException("Some Json error");
    }
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