//
// Created by vladislav on 19.05.22.
//

#ifndef SERVER_V0_1_ERRORS_HPP
#define SERVER_V0_1_ERRORS_HPP

#include <stdexcept>

namespace Error {

class url_error : public std::runtime_error {
public:
    using runtime_error::runtime_error;
};

class too_big_error : public std::runtime_error {
public:
    using runtime_error::runtime_error;
};

}   // namespace Error

#endif //SERVER_V0_1_ERRORS_HPP
