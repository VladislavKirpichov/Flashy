//
// Created by vladislav on 27.05.22.
//

#ifndef SERVER_V0_1_STORAGE_H
#define SERVER_V0_1_STORAGE_H

#include <string>
#include <type_traits>

//template <typename std::string>
//concept is_writable = std::is_convertible_v<std::string, std::basic_string<char>>;
//
//template <typename std::string>
//requires is_writable<std::string>
class Storage {
public:
    // std::stringODO: сделать const Page& page
    std::string create_file(const std::string& login, std::string&& input_data);
    std::string get_file(const std::string& login, const std::string& file_url);
    void update_file_header(const std::string& file_url);
    void update_file_body(const std::string& file_url, std::string&& input_data);
    void delete_file(const std::string& file_url);

protected:
    // void write_page_header_in_file(const std::string& file_url, Page& page);
    void write_input_data_in_file(const std::string& file_url, std::string&& input_data);

private:
    std::string generate_random_name(const std::string& login);
    static inline unsigned max_file_name = 8;
    static inline std::string_view chars = {"0123456789"
                                            "ABCDEFGHIJKLMNOPQRSzUVWXYZ"
                                            "abcdefghijklmnopqrstuvwxyz"};

    static inline std::string data_path = "data/";
};


#endif //SERVER_V0_1_Sstd::stringORAGE_H
