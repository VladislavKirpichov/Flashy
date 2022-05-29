//
// Created by vladislav on 19.05.22.
//

#include <boost/algorithm/string/predicate.hpp>

#include "HttpParser.h"
#include "Exceptions.h"

#define MAX_VAR_NAME_LENGTH 50
#define MAX_VAR_VALUE_LENGTH 32 // int max length

std::string_view HttpParser::define_page_type(const std::string& url_path) noexcept(false) {
    if (boost::starts_with(url_path, "/user") || boost::starts_with(url_path, "/user/"))
        return {"user"};
    else if (boost::starts_with(url_path, "/page") || boost::starts_with(url_path, "/page/"))
        return {"page"};
    else if (boost::starts_with(url_path, "/auth") || boost::starts_with(url_path, "/auth/"))
        return {"auth"};
    else if (boost::starts_with(url_path, "/question") || boost::starts_with(url_path, "/question/"))
        return {"question"};
    else if (boost::starts_with(url_path, "/signup") || boost::starts_with(url_path, "/signup/"))
        return {"signup"};
    else
        throw HttpException::NotDefinedType("not type of user || page || auth || signup || question");
}

std::vector<std::tuple<std::string, std::string>> HttpParser::define_args(const std::string& url_path) {
    // find where args starts
    auto args_start = std::find(url_path.begin(), url_path.end(), '?');
    if (args_start == url_path.end())
        throw HttpException::InvalidArguments("? not found");

    std::string var_name{};
    std::string var_value{};
    std::vector<std::tuple<std::string, std::string>> return_vars{};

    auto search_var_name = [&](std::string::const_iterator& start_from) -> void {
        var_name = std::string(start_from, std::find(start_from, url_path.end(), '='));

        if (var_name.empty() || var_name.size() > MAX_VAR_NAME_LENGTH)
            throw HttpException::InvalidArguments("search_var_name");

        start_from = std::find(start_from, url_path.end(), '=');
        start_from++;   // skip '='
    };

    auto search_var_value = [&](std::string::const_iterator& start_from,
                                const std::vector<char>& end_of_value_symbols) -> void {
        var_value = std::string(start_from, std::find_first_of(start_from, url_path.end(), end_of_value_symbols.begin(), end_of_value_symbols.end()));

        if (var_value.empty() || var_value.size() > MAX_VAR_VALUE_LENGTH)
            throw HttpException::InvalidArguments("search_var_value");

        start_from = std::find_first_of(start_from, url_path.end(), end_of_value_symbols.begin(), end_of_value_symbols.end());
    };

    std::vector<char> end_of_value_symbols {'&', '/', '?'};

    // start from '?'
    auto i = args_start++;
    while (i != url_path.end()) {
        if (*i == '&' || *i == '?')
            i++;

        search_var_name(i);
        search_var_value(i, end_of_value_symbols);

        return_vars.emplace_back(var_name, var_value);

        // reset vars
        var_name.clear();
        var_value.clear();
    }


  return return_vars;
}

std::unordered_map<std::string, std::string> HttpParser::define_args_map(const std::string& url_path) {
    // find where args starts
    auto args_start = std::find(url_path.begin(), url_path.end(), '?');
    if (args_start == url_path.end())
        throw HttpException::InvalidArguments("? not found");

    std::string var_name{};
    std::string var_value{};
    std::unordered_map<std::string, std::string> return_vars{};

    auto search_var_name = [&](std::string::const_iterator& start_from) -> void {
        var_name = std::string(start_from, std::find(start_from, url_path.end(), '='));

        if (var_name.empty() || var_name.size() > MAX_VAR_NAME_LENGTH)
            throw HttpException::InvalidArguments("search_var_name");

        start_from = std::find(start_from, url_path.end(), '=');
        start_from++;   // skip '='
    };

    auto search_var_value = [&](std::string::const_iterator& start_from,
                                const std::vector<char>& end_of_value_symbols) -> void {
        var_value = std::string(start_from, std::find_first_of(start_from, url_path.end(), end_of_value_symbols.begin(), end_of_value_symbols.end()));

        if (var_value.empty() || var_value.size() > MAX_VAR_VALUE_LENGTH)
            throw HttpException::InvalidArguments("search_var_value");

        start_from = std::find_first_of(start_from, url_path.end(), end_of_value_symbols.begin(), end_of_value_symbols.end());
    };

    std::vector<char> end_of_value_symbols {'&', '/', '?'};

    // start from '?'
    auto i = args_start++;
    while (i != url_path.end()) {
        if (*i == '&' || *i == '?')
            i++;

        search_var_name(i);
        search_var_value(i, end_of_value_symbols);

        return_vars[var_name] = var_value;

        // reset vars
        var_name.clear();
        var_value.clear();
    }


    return return_vars;
}
