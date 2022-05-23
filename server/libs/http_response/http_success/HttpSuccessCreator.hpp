//
// Created by vladislav on 22.05.22.
//

#ifndef SERVER_V0_1_HTTPSUCCESSCREATOR_HPP
#define SERVER_V0_1_HTTPSUCCESSCREATOR_HPP

#include <memory>
#include "HttpSuccess.hpp"

template<typename Send>
class HttpSuccessCreator {
public:
    static std::shared_ptr<Ok200<Send>> create_ok_200(Send&& send, unsigned response_version);
};

template<typename Send>
std::shared_ptr<Ok200<Send>> HttpSuccessCreator<Send>::create_ok_200(Send &&send, unsigned int response_version) {
    return std::make_shared<Ok200<Send>>(std::move(send), response_version);
}

#endif //SERVER_V0_1_HTTPSUCCESSCREATOR_HPP
