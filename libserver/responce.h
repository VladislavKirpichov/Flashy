#ifndef RESPONSE_H
#define RESPONSE_H

struct Response
{
    int status_code;
    std::string status_message;
    std::vector<std::string> headers;
    std::string body;
    std::string http_version;
};

inline std::string Response2String(const Response &response) {
    std::string res = "responce";
    return res;
}

#endif //RESPONSE_H