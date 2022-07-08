//
// Created by vladislav on 24.05.22.
//

#include "gtest/gtest.h"
#include "JsonSerializer.h"
#include "User.h"

TEST(JSON, user_serialize) {
    User test_user{};
    std::string right_answer = "{\"email\":\"test_email@gmail.com\",\"id\":1,\"login\":\"test_user\",\"password\":\"123\",\"status\":\"student\"}";

    std::string answer = JsonSerializer::serialize_user(test_user);
    EXPECT_EQ(answer, right_answer);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}