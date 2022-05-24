//
// Created by vladislav on 24.05.22.
//

#include "gtest/gtest.h"
#include "HttpParser.h"
#include "Exceptions.h"

TEST(http_parser, define_page_type__user) {
    std::string test_url_1 = "/user/";
    EXPECT_EQ("user", HttpParser::define_page_type(test_url_1));
    std::string test_url_2 = "/user";
    EXPECT_EQ("user", HttpParser::define_page_type(test_url_2));
}

TEST(http_parser, define_page_type__page) {
    std::string test_url_1 = "/page/";
    EXPECT_EQ("page", HttpParser::define_page_type(test_url_1));
    std::string test_url_2 = "/page";
    EXPECT_EQ("page", HttpParser::define_page_type(test_url_2));
}

TEST(http_parser, define_page_type__auth) {
    std::string test_url_1 = "/auth/";
    EXPECT_EQ("auth", HttpParser::define_page_type(test_url_1));
    std::string test_url_2 = "/auth";
    EXPECT_EQ("auth", HttpParser::define_page_type(test_url_2));
}

TEST(http_parser, define_page_type__test) {
    std::string test_url_1 = "/test/";
    EXPECT_EQ("test", HttpParser::define_page_type(test_url_1));
    std::string test_url_2 = "/test";
    EXPECT_EQ("test", HttpParser::define_page_type(test_url_2));
}

TEST(http_parser, define_page_type__exception) {
    std::string test_url = "/some_test/";

    EXPECT_THROW({
                     try {
                         HttpParser::define_page_type(test_url);
                     }
                     catch (HttpException::NotDefinedType& ec) {
                         EXPECT_STREQ("Http Parser Exception: not type of user || page || auth || test", ec.what());
                         throw ec;
                     }
                 }, HttpException::NotDefinedType);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}