//
// Created by vladislav on 19.05.22.
//

#ifndef SERVER_V0_1_HTTPPARSER_H
#define SERVER_V0_1_HTTPPARSER_H

#include <string>
#include <vector>
#include <tuple>

class HttpParser {
public:
    static std::string_view define_page_type(const std::string& url_path);
    static std::vector<std::tuple<std::string , std::string>> define_args(const std::string& url_path);
    static std::unordered_map<std::string, std::string> define_args_map(const std::string& url_path);
};


#endif //SERVER_V0_1_HTTPPARSER_H
