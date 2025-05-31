#include <gtest/gtest.h>
#include <nlohmann/json.hpp> // Example: If you want to test nlohmann_json

// Sample function to test
int add(int a, int b) {
    return a + b;
}

// Unit test for the `add` function
TEST(AdditionTests, HandlesPositiveNumbers) {
    EXPECT_EQ(add(1, 2), 3);
    EXPECT_EQ(add(10, 15), 25);
}

TEST(AdditionTests, HandlesNegativeNumbers) {
    EXPECT_EQ(add(-1, -1), -2);
    EXPECT_EQ(add(-5, 5), 0);
}

// Test for third-party library (optional, example with nlohmann_json)
TEST(JsonTests, ParseSimpleJson) {
    std::string json_str = R"({"key": "value", "number": 42})";
    auto json = nlohmann::json::parse(json_str);

    EXPECT_EQ(json["key"], "value");
    EXPECT_EQ(json["number"], 42);
}//
// Created by LENOVO on 31/05/2025.
//
