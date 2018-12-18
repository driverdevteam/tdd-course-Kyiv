#include <gtest/gtest.h>

/*
Convert a ternary number, represented as a string (e.g. '102012'), to its decimal equivalent using first principles.

The program should consider strings specifying an invalid ternary as the value 0.

Ternary numbers contain three symbols: 0, 1, and 2.

The last place in a ternary number is the 1's place. The second to last is the 3's place, the third to last is the 9's place, etc.

# "102012"
    1       0       2       0       1       2    # the number
1*3^5   + 0*3^4 + 2*3^3 + 0*3^2 + 1*3^1 + 2*3^0    # the value
  243   +   0 +    54 +     0 +     3 +     2 =  302

If your language provides a method in the standard library to perform the conversion, pretend it doesn't exist and implement it yourself.
*/

/*
 * 1) 0 test
 * 2) 1 test
 * 3) 2 test
 * 4) invalid digit test
 * 5) Multiple digits tests
 * 6) Invalid multiple digits tests
 * 7) Acceptence test
 */

bool TernaryNumber(int number)
{
    return number < 3;
}

int ConvertTernaryNumbers(const std::string &number)
{
    int sum = 0;
    for (int index = 0; index < number.size(); ++index)
    {
        int numberValue = std::stoi(std::string(1, number[number.size() - 1 - index]));
        if (!TernaryNumber(numberValue))
        {
            return 0;
        }
        sum += numberValue * std::pow(3, index);
    }

    return sum;
}

TEST(TernaryNumbers, ZeroTest)
{
    ASSERT_TRUE(TernaryNumber(0));
}

TEST(TernaryNumbers, CheckOne)
{
    ASSERT_TRUE(TernaryNumber(1));
}

TEST(TernaryNumbers, CheckTwo)
{
    ASSERT_TRUE(TernaryNumber(2));
}

TEST(TernaryNumbers, InvalidDigit)
{
    ASSERT_FALSE(TernaryNumber(3));
}

TEST(TernaryNumbers, MultipleDigits)
{
    ASSERT_EQ(0, ConvertTernaryNumbers("00"));
}

TEST(TernaryNumbers, MultipleDigits111)
{
    ASSERT_EQ(13, ConvertTernaryNumbers("111"));
}

TEST(TernaryNumbers, InvalidMultipleDigits)
{
    ASSERT_EQ(0, ConvertTernaryNumbers("113"));
}

TEST(TernaryNumbers, Acceptance)
{
    ASSERT_EQ(0, ConvertTernaryNumbers("123"));
    ASSERT_EQ(16, ConvertTernaryNumbers("121"));
    ASSERT_EQ(439, ConvertTernaryNumbers("121021"));
    ASSERT_EQ(597871, ConvertTernaryNumbers("1010101010101"));
}
