//
// Created by vladislav on 19.05.22.
//

#include "JsonSerializer.h"
#include "nlohmann/json.hpp"
#include <iostream>

std::string JsonSerializer::serialize(const std::vector<std::vector<std::string>>& input_data) {
    nlohmann::json json_data{};
    std::vector<std::string>::const_iterator value_it{};

    for (auto& field : input_data) {
        value_it = field.begin() + 1;
        if (field.size() == 2)
            json_data[*field.begin()] = *value_it;
        else
            for (; value_it != field.end(); ++value_it)
                json_data[*field.begin()] += *value_it;
    }

    return to_string(json_data);
}

std::string JsonSerializer::serialize(const std::vector<std::tuple<std::string, std::string>>& input_data) {
    nlohmann::json json_data{};
    std::vector<std::string>::const_iterator value_it{};

    std::cout << "json_start\n";

    for (auto& field : input_data)
        json_data[std::get<0>(field)] = std::basic_string(std::get<1>(field));

    std::cout << "end\n";

    return to_string(json_data);
}