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

#include <cmath>

const unsigned int MaxNumber = 2;
const unsigned int PowNumeber = 3;
const unsigned int IndexMultiplier = 3;

unsigned int TernaryNumber(unsigned int index, unsigned int number)
{
    if (number > MaxNumber)
    {
        return 0;
    }

    return number * static_cast<unsigned int>(std::pow(PowNumeber, index));
}

unsigned int ConvertTernaryNumbers(const std::string &numbers)
{
    if (numbers.empty())
    {
        return 0;
    }

    unsigned int sum = 0;
    for (auto rIter = numbers.rbegin(); rIter != numbers.rend(); ++rIter)
    {
        unsigned int number = std::stoul(std::string(1, *rIter));
        if (number > MaxNumber)
        {
            return 0;
        }

        unsigned int rIterIndex = rIter - numbers.rbegin();
        unsigned int place = rIterIndex == 0 ? 1 : rIterIndex * IndexMultiplier;
        unsigned int num = TernaryNumber(place, number);

        sum += num;
    }

    return sum;
}

TEST(TernaryNumbers, OneNumber)
{
    ASSERT_EQ(3, TernaryNumber(1, 1));
}

TEST(TernaryNumbers, WrongNumber)
{
    ASSERT_EQ(0, TernaryNumber(1, 3));
}

TEST(TernaryNumbers, OneIndexTwoNumber)
{
    ASSERT_EQ(6, TernaryNumber(1, 2));
}

TEST(TernaryNumbers, EmptyNumberString)
{
    ASSERT_EQ(0, ConvertTernaryNumbers(""));
}

TEST(TernaryNumbers, OneNumberString)
{
    ASSERT_EQ(3, ConvertTernaryNumbers("1"));
}

TEST(TernaryNumbers, MultipleNumberString)
{
    ASSERT_EQ(27, ConvertTernaryNumbers("10"));
}

TEST(TernaryNumbers, WrongMultipleNumberString)
{
    ASSERT_EQ(0, ConvertTernaryNumbers("13"));
}

TEST(TernaryNumbers, Acceptence)
{
    ASSERT_EQ(0, ConvertTernaryNumbers("3102"));
    ASSERT_EQ(0, ConvertTernaryNumbers("0"));
    ASSERT_EQ(6, ConvertTernaryNumbers("02"));
    ASSERT_EQ(19743, ConvertTernaryNumbers("1022"));
}
