//
// Created by vladislav on 24.05.22.
//

#ifndef SERVER_V0_1_PAGE_H
#define SERVER_V0_1_PAGE_H

#include <string>
#include <vector>

class Page {
public:
    void page_connect_DB();

    void page_close_connect();

    void add_page(size_t user_ID, std::string title, std::string file, std::string mime, std::string url);

    std::vector<std::vector<std::string>> get_page_ID(std::string page_title);

    std::vector<std::vector<std::string>> get_all_page_info(size_t page_ID);

    std::vector<std::vector<std::string>> get_all_user_pages(size_t user_ID);

    std::vector<std::vector<std::string>> get_user_ID(size_t page_ID);

    void update_page_title(size_t page_ID, std::string new_title);

    std::vector<std::vector<std::string>> get_page_title(size_t page_ID);

    std::vector<std::vector<std::string>> get_created_time(size_t page_ID);

    void set_updated_time(size_t page_ID);

    std::vector<std::vector<std::string>> get_updated_time(size_t page_ID);

    void set_last_visited_time(size_t page_ID);

    std::vector<std::vector<std::string>> get_last_visited_time(size_t page_ID);

    void update_file_page(size_t page_ID, std::string new_file);

    std::vector<std::vector<std::string>> get_file_page(size_t page_ID);

    void update_page_mime(size_t page_ID, std::string new_mime);

    std::vector<std::vector<std::string>> get_page_mime(size_t page_ID);

    void update_page_url(size_t page_ID, std::string new_url);

    std::vector<std::vector<std::string>> get_page_url(size_t page_ID);

    void delete_page(size_t page_ID);

    size_t get_id() const { return id; }
    size_t get_login() const { return login; }
    std::string get_title() const { return title; }
    time_t get_created_time() const { return created_time; }
    time_t get_updated_time() const { return updated_time; }
    time_t get_last_visited_time() const { return last_visited_time; }
    std::string get_file() const { return file; }
    std::string get_mime() const { return mime; }
    std::string get_url() const { return url; }

private:
    size_t id;
    size_t login;
    std::string title;
    time_t created_time;
    time_t updated_time;
    time_t last_visited_time;
    std::string file;
    std::string mime;
    std::string url;
    // DB *database;
};

#endif //SERVER_V0_1_PAGE_H
