//
// Created by vladislav on 14.05.22.
//

#ifndef SERVER_V0_1_JSON_SERIALAIZER_HPP
#define SERVER_V0_1_JSON_SERIALAIZER_HPP

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

boost::property_tree::ptree deserialize(std::string str) {
    boost::property_tree::ptree root;
}

std::string serialize(boost::property_tree::ptree);

#endif //SERVER_V0_1_JSON_SERIALAIZER_HPP
