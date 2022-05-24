//
// Created by vladislav on 19.05.22.
//

#ifndef SERVER_V0_1_JSONSERIALIZER_HPP
#define SERVER_V0_1_JSONSERIALIZER_HPP

#include <vector>
#include <string>
#include <tuple>

template <typename T>
class EntitiesJsonSerializer {
public:
    static std::string serialize (const T& input_data);
    static T deserialize (const std::string& input_data);
};


struct JsonSerializer {
    static std::string serialize(const std::vector<std::vector<std::string>>& input_data);
    static std::string serialize(const std::vector<std::tuple<std::string , std::string>>& input_data);
    static std::vector<std::vector<std::string>> deserialize(const std::string& json_str);

private:
    JsonSerializer() = default;
    ~JsonSerializer() = default;
    JsonSerializer(JsonSerializer& json_serializer) = default;
    JsonSerializer& operator=(JsonSerializer& json_serializer) = default;
};


#endif //SERVER_V0_1_JSONSERIALIZER_HPP
