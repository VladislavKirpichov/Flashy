#ifndef REQUEST_H
#define REQUEST_H

struct Request
{
    std::string host;
    std::string method;
    std::string path;
    std::vector<std::string> params;
    std::vector<std::string> headers;
    std::string body;
    std::string http_version;
};

// inline std::ostream& operator<<(std::ostream& os, const Request& request);

std::string Request2String(const Request &request) {
    std::string req = "request";
    return req;
}

#endif //REQUEST_H