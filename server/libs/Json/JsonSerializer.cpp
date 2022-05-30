//
// Created by vladislav on 19.05.22.
//

#include "JsonSerializer.h"
#include "nlohmann/json.hpp"
#include "Exceptions.h"


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
        throw JsonException::JsonException();
    }
}

std::unordered_map<std::string, std::vector<std::string>> JsonSerializer::deserialize_in_vector(const std::string& json_str) {
    try {
        nlohmann::json json_data = nlohmann::json::parse(json_str);
        std::unordered_map<std::string, std::vector<std::string>> data{};

        for (auto &[key, value]: json_data.items())
            for (auto&i : value)
                data[key].push_back(i);

        return data;
    }
    catch (nlohmann::json::exception& ec) {
        throw JsonException::JsonException(ec);
    }
    catch (...) {
        throw JsonException::JsonException();
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

        json_data["pages_id"];
        for (auto& i : user.get_pages_file())
            json_data["pages_id"] += i[0];

        json_data["pages_titles"];
        for (auto& i : user.get_pages_title())
            json_data["pages_titles"] += i[0];

        return to_string(json_data);
    }
    catch (nlohmann::json::exception& ec) {
        throw JsonException::JsonException(ec);
    }
    catch (...) {
        throw JsonException::JsonException();
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

        json_data["questions_id"];
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
        json_data["question"] = question.get_question_file();
        json_data["answer"] = question.get_question_answer();
        json_data["right_answers"] = question.get_right_answers_count();
        json_data["wrong_answers"] = question.get_wrong_answers();
        json_data["right_answers_rate"] = question.get_right_answers_rate();

        return to_string(json_data);
    }
    catch (nlohmann::json::exception& ec) {
        throw JsonException::JsonException(ec);
    }
    catch (...) {
        throw JsonException::JsonException("Some Json error");
    }
}