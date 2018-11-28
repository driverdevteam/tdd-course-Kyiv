#include <gtest/gtest.h>
#include <math.h>

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

const std::string g_ternary302 = "102012";
const std::string g_ternary303 = "102020";
const std::string g_ternary304 = "102021";
const std::string g_ternary305 = "102022";


const std::string g_ternary222 = "22020";
const std::string g_ternary333 = "110100";
const std::string g_ternary765 = "1001100";
const std::string g_ternary345 = "110210";


uint32_t convert(const std::string &number)
{
    if (number.empty())
        return -1;

    int result = 0;
    int place = number.size();
    for (const char& a: number)
    {
        result += (a - '0') * std::pow(3, --place);
    }
    return result;
}

TEST (ternary_numbers, check_302)
{
    EXPECT_EQ(302, convert(g_ternary302));
}

TEST (ternary_numbers, check_303)
{
    EXPECT_EQ(303, convert(g_ternary303));
}

TEST (ternary_numbers, check_304)
{
    EXPECT_EQ(304, convert(g_ternary304));
}

TEST (ternary_numbers, check_305)
{
    EXPECT_EQ(305, convert(g_ternary305));
}

TEST (ternary_numbers, acceptance)
{
    EXPECT_EQ(222, convert(g_ternary222));
    EXPECT_EQ(333, convert(g_ternary333));
    EXPECT_EQ(765, convert(g_ternary765));
    EXPECT_EQ(345, convert(g_ternary345));
    EXPECT_EQ(-1, convert(""));
}
