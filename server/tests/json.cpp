//
// Created by vladislav on 27.05.22.
//

#include "gtest/gtest.h"

#include "JsonSerializer.h"
#include "User.h"

TEST(Json, serialize_user) {
    std::string answer{"{\"email\":\"new_email\",\"id\":5,\"login\":\"Bob\",\"pages_id\":[\"\"],\"pages_titles\":[\"\"],\"password\":\"321\",\"status\":\"student\"}"};
    User user{"Bob"};
    EXPECT_EQ(answer, JsonSerializer::serialize_user(user));
}

TEST(Json, ) {

}

TEST(Json, deserialize_in_vector) {
    auto test = JsonSerializer::deserialize_in_vector("{\"hello\":\"from\", \"this\": [\"amazing\", \"json\"]}");

    EXPECT_EQ("from", test.at("hello")[0]);
    EXPECT_EQ("amazing", test.at("this")[0]);
    EXPECT_EQ("json", test.at("this")[1]);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}