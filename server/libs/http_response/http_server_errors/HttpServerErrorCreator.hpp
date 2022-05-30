//
// Created by vladislav on 22.05.22.
//

#ifndef SERVER_V0_1_HTTPSERVERERRORCREATOR_HPP
#define SERVER_V0_1_HTTPSERVERERRORCREATOR_HPP

#include "HttpServerErrors.hpp"

template<typename Send>
class HttpServerErrorCreator {
public:
    static std::shared_ptr<InternalServerError500<Send>> create_internal_server_error_500(Send&& send, unsigned response_version);
    static std::shared_ptr<NotImplemented501<Send>> create_not_implemented_501(Send&& send, unsigned response_version);
    static std::shared_ptr<ServiceUnavailable503<Send>> create_service_unavailable_503(Send&& send, unsigned response_version);
};

template<typename Send>
std::shared_ptr<InternalServerError500<Send>>
HttpServerErrorCreator<Send>::create_internal_server_error_500(Send &&send, unsigned int response_version) {
    return std::make_shared<InternalServerError500<Send>>(std::move(send), response_version);
}

template<typename Send>
std::shared_ptr<NotImplemented501<Send>>
HttpServerErrorCreator<Send>::create_not_implemented_501(Send &&send, unsigned int response_version) {
    return std::make_shared<NotImplemented501<Send>>(std::move(send), response_version);
}

template<typename Send>
std::shared_ptr<ServiceUnavailable503<Send>>
HttpServerErrorCreator<Send>::create_service_unavailable_503(Send &&send, unsigned int response_version) {
    return std::make_shared<ServiceUnavailable503<Send>>(std::move(send), response_version);
}


#endif //SERVER_V0_1_HTTPSERVERERRORCREATOR_HPP
