/*
Reverse a string

For example: input: "cool" output: "looc"
             input: "12345" output: "54321"
             input: "123456" output: "654321"
*/

#include <gtest/gtest.h>

const std::string g_textToReverse = "Reversed";
const std::string g_textReversed = "desreveR";

std::string ReverseString(const std::string& str)
{
    std::string reversedStr(str);
    std::reverse(reversedStr.begin(), reversedStr.end());

    return reversedStr;
}

TEST(intro, StringIsReversed)
{
    ASSERT_EQ(g_textReversed, ReverseString(g_textToReverse));
}
