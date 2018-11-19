/*
Reverse a string

For example: input: "cool" output: "looc"
             input: "12345" output: "54321"
             input: "123456" output: "654321"
*/

#include <gtest/gtest.h>

std::string ReverseString(const std::string& str)
{
    return "";
}

TEST(intro, StringIsReversed)
{
    ASSERT_EQ("desreveR", ReverseString("Reversed"));
}
