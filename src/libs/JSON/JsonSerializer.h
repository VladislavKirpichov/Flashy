//
// Created by vladislav on 19.05.22.
//

#ifndef SERVER_V0_1_JSONSERIALIZER_HPP
#define SERVER_V0_1_JSONSERIALIZER_HPP

#include <vector>
#include <string>
#include <tuple>

struct JsonSerializer {
    static std::string serialize(const std::vector<std::vector<std::string>>& input_data);
    static std::string serialize(const std::vector<std::tuple<std::string , std::string>>& input_data);

private:
    JsonSerializer() = default;
    ~JsonSerializer() = default;
    JsonSerializer(JsonSerializer& json_serializer) = default;
    JsonSerializer& operator=(JsonSerializer& json_serializer) = default;
};


#endif //SERVER_V0_1_JSONSERIALIZER_HPP
