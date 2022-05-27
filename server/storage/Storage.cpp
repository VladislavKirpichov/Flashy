//
// Created by vladislav on 27.05.22.
//

#include "Storage.h"

#include <iostream>
#include <fstream>
#include <cstdio>
#include <random>
#include <time.h>

#define FILE_EXTENSION ".txt"

//template <typename T>
//requires is_writable
std::string Storage::create_file(const std::string& login, std::string&& input_data) {
    std::string file_url = login + '_' + this->generate_random_name(login);
    std::cout << "file_name = " << file_url << '\n';

    write_input_data_in_file(file_url, std::move(input_data));

    return file_url;
}

std::string Storage::get_file(const std::string& login, const std::string& file_url) {
    std::ifstream i_file{"data/vlad_MfifXu9u.txt"};
    std::string data;

    char temp;
    while (i_file.get(temp))
        data += temp;

    i_file.close();

    return data;
}

std::string Storage::generate_random_name(const std::string& login) {
    std::string name{};
    std::srand(time(0));

    for (unsigned i = 0; i < max_file_name; ++i)
        name += chars[std::rand() % chars.size()];

    return name;
}

void Storage::write_input_data_in_file(const std::string& file_url, std::string&& input_data) {
    std::ofstream o_file{data_path + file_url + FILE_EXTENSION};
    o_file << input_data << std::endl;
    o_file.close();
}

void Storage::update_file_body(const std::string &file_url, std::string&& input_data) {
    std::ofstream o_file{data_path + file_url + FILE_EXTENSION};
    o_file.clear();
    o_file << input_data << std::endl;
    o_file.close();
}

void Storage::delete_file(const std::string &file_url) {
    std::string remove_file_path = data_path + file_url + FILE_EXTENSION;
    std::remove(remove_file_path.c_str());
}