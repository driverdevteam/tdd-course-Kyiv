/*
Reverse a string

For example: input: "cool" output: "looc"
             input: "12345" output: "54321"
             input: "123456" output: "654321"
*/

#include <gtest/gtest.h>

const std::string g_testStringCool = "cool";
const std::string g_testReverseStringCool = "looc";
const std::string g_testString12345 = "12345";
const std::string g_testReverseString12345 = "54321";
const std::string g_testString123456 = "123456";
const std::string g_testReverseString123456 = "654321";
const std::string g_testOutOfScopeCaseString = "some random input to cover more cases";
const std::string g_testReverseOutOfScopeCaseString = "sesac erom revoc ot tupni modnar emos";

std::string ReverseAString(const std::string& target)
{
    std::string result(target);
    std::reverse(result.begin(), result.end());
    return result;
}

TEST(reverse, CheckCoolString)
{
    ASSERT_EQ(g_testReverseStringCool, ReverseAString(g_testStringCool));
}

TEST(reverse, Check12345String)
{
    ASSERT_EQ(g_testReverseString12345, ReverseAString(g_testString12345));
}

TEST(reverse, Check123456String)
{
    ASSERT_EQ(g_testReverseString123456, ReverseAString(g_testString123456));
}

TEST(reverse, CheckOtherString)
{
    ASSERT_EQ(g_testReverseOutOfScopeCaseString, ReverseAString(g_testOutOfScopeCaseString));
}
