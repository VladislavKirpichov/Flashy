//
// Created by vladislav on 20.05.22.
//

#ifndef SERVER_V0_1_HTTPERRORCREATOR_HPP
#define SERVER_V0_1_HTTPERRORCREATOR_HPP

#include <memory>

#include "HttpErrors.hpp"

template<typename Send>
class HttpErrorCreator {
public:
    static std::shared_ptr<BadRequest400<Send>> create_bad_request_400(Send&& send, unsigned response_version);
    static std::shared_ptr<Unauthorized401<Send>> create_unauthorized_401(Send&& send, unsigned response_version);
    static std::shared_ptr<Forbidden403<Send>> create_forbidden_403(Send&& send, unsigned response_version);
    static std::shared_ptr<NotFound404<Send>> create_not_found_404(Send&& send, unsigned response_version);
    static std::shared_ptr<MethodNotAllowerd405<Send>> create_method_not_allowed_405(Send&& send, unsigned response_version);
    static std::shared_ptr<RequestTimeOut408<Send>> create_request_timeout_408(Send&& send, unsigned response_version);
    static std::shared_ptr<UnsupportedMediaType415<Send>> create_unsupported_media_Type_415(Send&& send, unsigned response_version);
};

template<typename Send>
std::shared_ptr<BadRequest400<Send>>
HttpErrorCreator<Send>::create_bad_request_400(Send&& send, unsigned response_version) {
    return std::make_shared<BadRequest400<Send>>(std::move(send), response_version);
}

template<typename Send>
std::shared_ptr<Unauthorized401<Send>>
HttpErrorCreator<Send>::create_unauthorized_401(Send&& send, unsigned response_version) {
    return std::make_shared<Unauthorized401<Send>>(std::move(send), response_version);
}

template<typename Send>
std::shared_ptr<Forbidden403<Send>>
HttpErrorCreator<Send>::create_forbidden_403(Send &&send, unsigned int response_version) {
    return std::make_shared<Forbidden403<Send>>(std::move(send), response_version);
}

template<typename Send>
std::shared_ptr<NotFound404<Send>>
HttpErrorCreator<Send>::create_not_found_404(Send &&send, unsigned int response_version) {
    return std::make_shared<NotFound404<Send>>(std::move(send), response_version);
}

template<typename Send>
std::shared_ptr<MethodNotAllowerd405<Send>>
HttpErrorCreator<Send>::create_method_not_allowed_405(Send &&send, unsigned int response_version) {
    return std::make_shared<MethodNotAllowerd405<Send>>(std::move(send), response_version);
}

template<typename Send>
std::shared_ptr<RequestTimeOut408<Send>>
HttpErrorCreator<Send>::create_request_timeout_408(Send &&send, unsigned int response_version) {
    return std::make_shared<RequestTimeOut408<Send>>(std::move(send), response_version);
}

template<typename Send>
std::shared_ptr<UnsupportedMediaType415<Send>>
HttpErrorCreator<Send>::create_unsupported_media_Type_415(Send &&send, unsigned int response_version) {
    return std::make_shared<UnsupportedMediaType415<Send>>(std::move(send), response_version);
}


#endif //SERVER_V0_1_HTTPERRORCREATOR_HPP
