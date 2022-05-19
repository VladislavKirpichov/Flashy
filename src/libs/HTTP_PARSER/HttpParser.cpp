//
// Created by vladislav on 19.05.22.
//

#include <boost/algorithm/string/predicate.hpp>
#include <algorithm>

#include "Errors.hpp"
#include "HttpParser.h"

#define MAX_VAR_NAME_LENGTH 50
#define MAX_VAR_VALUE_LENGTH 32 // int max length

std::string_view HttpParser::define_page_type(const std::string& url_path) noexcept(false) {
    if (boost::starts_with(url_path, "/user") || boost::starts_with(url_path, "/user/"))
        return {"user"};
    else if (boost::starts_with(url_path, "/page") || boost::starts_with(url_path, "/page/"))
        return {"page"};
    else if (boost::starts_with(url_path, "/auth") || boost::starts_with(url_path, "/auth/"))
        return {"auth"};
    else if (boost::starts_with(url_path, "/test") || boost::starts_with(url_path, "/test/"))
        return {"test"};
    else
        throw Error::url_error("url error");
}

std::vector<std::tuple<std::string, std::string>> HttpParser::define_args(const std::string& url_path) {
    // find where args starts
    auto args_start = std::find(url_path.begin(), url_path.end(), '?');

    // vars for search
    std::string var_name{};
    std::string var_value{};
    unsigned char counter{0};
    std::vector<std::tuple<std::string, std::string>> return_vars{};

    // start from '?'
    for (auto i = args_start; i != url_path.end(); i++) {
        if (*i == '&' || *i == '?')
            i++;

        // get var name
        while (*i != '=' && i != url_path.end() && counter <= MAX_VAR_NAME_LENGTH) {
            var_name += *i++;
            counter++;
        }

        if (i == url_path.end())
            break;  // throw error

        if (counter > MAX_VAR_NAME_LENGTH)
            break;  // throw error

        counter = 0;

        // get var value
        if (*i++ == '=') {
            while (*i != '&' && i != url_path.end() && counter <= MAX_VAR_VALUE_LENGTH) {
                var_value += *i++;
                counter++;
            }
        }

        if (counter > MAX_VAR_NAME_LENGTH)
            break;  // throw error

        counter = 0;
        return_vars.emplace_back(var_name, var_value);
    }


  return return_vars;
}
