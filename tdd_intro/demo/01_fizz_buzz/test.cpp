#include <gtest/gtest.h>
#include <string>

/*
 * The program should answer "Fizz" if the input number is multiple of 3, Buzz - if you specify a number which is multiple of 5,
 * and FizzBuzz - if the number is a multiple of 3 and 5. In other cases the program should not answer. So, the conditions are:
 * a multiple of 3 = Fizz
 * a multiple of 5 = Buzz
 * a multiple of 15 = FizzBuzz
 * any other number = <nothing>
*/

const std::string g_fizzString = "Fizz";
const std::string g_buzzString = "Buzz";
const std::string g_fizzBuzzString = "FizzBuzz";

std::string FizzBuzz(int num)
{
    std::string fizzBuzzStr;

    if (num % 3 == 0)
    {
       fizzBuzzStr = g_fizzString;
    }

    if (num % 5 == 0)
    {
        fizzBuzzStr += g_buzzString;
    }

    return fizzBuzzStr;
}


TEST(FizzBuzzTest, Fizz)
{
    EXPECT_EQ(g_fizzString, FizzBuzz(3));
}

TEST(FizzBuzzTest, Buzz)
{
    EXPECT_EQ(g_buzzString, FizzBuzz(5));
}

TEST(FizzBuzzTest, Fizz6)
{
    EXPECT_EQ(g_fizzString, FizzBuzz(6));
}

TEST(FizzBuzzTest, Buzz10)
{
    EXPECT_EQ(g_buzzString, FizzBuzz(10));
}

TEST(FizzBuzzTest, FizzBuzz)
{
    EXPECT_EQ(g_fizzBuzzString, FizzBuzz(15));
}

TEST(FizzBuzzTest, FizzBuzzEmpty)
{
    EXPECT_EQ("", FizzBuzz(1));
}

TEST(FizzBuzzTest, Acceptance)
{
    EXPECT_EQ(g_buzzString, FizzBuzz(35));
    EXPECT_EQ(g_fizzString, FizzBuzz(66));
    EXPECT_EQ(g_fizzBuzzString, FizzBuzz(45));
    EXPECT_EQ("", FizzBuzz(17));
    EXPECT_EQ("", FizzBuzz(-23));
}
