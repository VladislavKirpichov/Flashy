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
