//
// Created by vladislav on 24.05.22.
//

#include "gtest/gtest.h"
#include "JsonSerializer.h"
#include "HttpParser.h"
#include "User.h"
#include "Exceptions.h"

TEST(some_test, hello) {
    EXPECT_EQ(1, 1);
}

TEST(JSON, user_serialize) {
    User test_user{};
    std::string right_answer = "{\"email\":\"test_email@gmail.com\",\"id\":1,\"login\":\"test_user\",\"password\":\"123\",\"status\":\"student\"}";

    std::string answer = JsonSerializer::serialize_user(test_user);
    EXPECT_EQ(answer, right_answer);
}

TEST(http_perser, define_page_type__user) {
    std::string test_url_1 = "/user/";
    EXPECT_EQ("user", HttpParser::define_page_type(test_url_1));
    std::string test_url_2 = "/user";
    EXPECT_EQ("user", HttpParser::define_page_type(test_url_2));
}

TEST(http_perser, define_page_type__page) {
    std::string test_url_1 = "/page/";
    EXPECT_EQ("page", HttpParser::define_page_type(test_url_1));
    std::string test_url_2 = "/page";
    EXPECT_EQ("page", HttpParser::define_page_type(test_url_2));
}

TEST(http_perser, define_page_type__auth) {
    std::string test_url_1 = "/auth/";
    EXPECT_EQ("auth", HttpParser::define_page_type(test_url_1));
    std::string test_url_2 = "/auth";
    EXPECT_EQ("auth", HttpParser::define_page_type(test_url_2));
}

TEST(http_perser, define_page_type__test) {
    std::string test_url_1 = "/test/";
    EXPECT_EQ("test", HttpParser::define_page_type(test_url_1));
    std::string test_url_2 = "/test";
    EXPECT_EQ("test", HttpParser::define_page_type(test_url_2));
}

TEST(http_perser, define_page_type__exception) {
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