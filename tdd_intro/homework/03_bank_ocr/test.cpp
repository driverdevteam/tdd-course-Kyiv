/*### Bank OCR

Your manager has recently purchased a machine that assists in reading letters and faxes sent in by branch offices. The machine scans the paper documents, and produces a file with a number of entries. You will write a program to parse this file.

#### Specification
#### User Story 1

The following format is created by the machine:
```
    _  _     _  _  _  _  _
  | _| _||_||_ |_   ||_||_|
  ||_  _|  | _||_|  ||_| _|
```
Each entry is 3 lines long, and each line has 27 characters. 3 lines of each entry contain an account number written using pipes and underscores.

Each account number should have 9 digits, all of which should be in the range 0-9. A normal file contains around 500 entries.

Write a program that can take this file and parse it into actual account numbers.

Example input and output
```
 _  _  _  _  _  _  _  _  _
| || || || || || || || || |
|_||_||_||_||_||_||_||_||_|

=> 000000000

  |  |  |  |  |  |  |  |  |
  |  |  |  |  |  |  |  |  |

=> 111111111

 _  _  _  _  _  _  _  _  _
 _| _| _| _| _| _| _| _| _|
|_ |_ |_ |_ |_ |_ |_ |_ |_

=> 222222222

 _  _  _  _  _  _  _  _  _
 _| _| _| _| _| _| _| _| _|
 _| _| _| _| _| _| _| _| _|

=> 333333333

|_||_||_||_||_||_||_||_||_|
  |  |  |  |  |  |  |  |  |

=> 444444444

 _  _  _  _  _  _  _  _  _
|_ |_ |_ |_ |_ |_ |_ |_ |_
 _| _| _| _| _| _| _| _| _|

=> 555555555

 _  _  _  _  _  _  _  _  _
|_ |_ |_ |_ |_ |_ |_ |_ |_
|_||_||_||_||_||_||_||_||_|

=> 666666666

 _  _  _  _  _  _  _  _  _
  |  |  |  |  |  |  |  |  |
  |  |  |  |  |  |  |  |  |

=> 777777777

 _  _  _  _  _  _  _  _  _
|_||_||_||_||_||_||_||_||_|
|_||_||_||_||_||_||_||_||_|

=> 888888888

 _  _  _  _  _  _  _  _  _
|_||_||_||_||_||_||_||_||_|
 _| _| _| _| _| _| _| _| _|

=> 999999999

    _  _     _  _  _  _  _
  | _| _||_||_ |_   ||_||_|
  ||_  _|  | _||_|  ||_| _|

=> 123456789
```
*/
#include <gtest/gtest.h>
#include <string>
#include <cmath>

const unsigned short g_digitLen = 3;
const unsigned short g_linesInDigit = 3;
struct Digit
{
    std::string lines[g_linesInDigit];
};

const unsigned short g_digitsOnDisplay = 9;
struct Display
{
    std::string lines[g_linesInDigit];
};

const Digit s_digit0 = { " _ ",
                         "| |",
                         "|_|"
                       };
const Digit s_digit1 = { "   ",
                         "  |",
                         "  |"
                       };
const Digit s_digit2 = { " _ ",
                         " _|",
                         "|_ "
                       };
const Digit s_digit3 = { " _ ",
                         " _|",
                         " _|"
                       };
const Digit s_digit4 = { "   ",
                         "|_|",
                         "  |"
                       };
const Digit s_digit5 = { " _ ",
                         "|_ ",
                         " _|"
                       };
const Digit s_digit6 = { " _ ",
                         "|_ ",
                         "|_|"
                       };
const Digit s_digit7 = { " _ ",
                         "  |",
                         "  |"
                       };
const Digit s_digit8 = { " _ ",
                         "|_|",
                         "|_|"
                       };
const Digit s_digit9 = { " _ ",
                         "|_|",
                         " _|"
                       };
const Digit s_incorrectDigit1 = { "   ",
                                  "|_|",
                                  " _|"
                                };
const Digit s_incorrectDigit2 = { "   ",
                                  "| |",
                                  "|_|"
                                };
const Digit s_incorrectDigit3 = { " _ ",
                                  "|_|",
                                  "| |"
                                };

const Display s_displayAll0 = { " _  _  _  _  _  _  _  _  _ ",
                                "| || || || || || || || || |",
                                "|_||_||_||_||_||_||_||_||_|"
};

const Display s_displayAll1 = { "                           ",
                                "  |  |  |  |  |  |  |  |  |",
                                "  |  |  |  |  |  |  |  |  |"
};

const Display s_displayAll2 = {  " _  _  _  _  _  _  _  _  _ ",
                                 " _| _| _| _| _| _| _| _| _|",
                                 "|_ |_ |_ |_ |_ |_ |_ |_ |_ "
};

const Display s_displayAll3 = { " _  _  _  _  _  _  _  _  _ ",
                                " _| _| _| _| _| _| _| _| _|",
                                " _| _| _| _| _| _| _| _| _|"
};

const Display s_displayAll4 = { "                           ",
                                "|_||_||_||_||_||_||_||_||_|",
                                "  |  |  |  |  |  |  |  |  |"
};

const Display s_displayAll5 = { " _  _  _  _  _  _  _  _  _ ",
                                "|_ |_ |_ |_ |_ |_ |_ |_ |_ ",
                                " _| _| _| _| _| _| _| _| _|"
};

const Display s_displayAll6 = { " _  _  _  _  _  _  _  _  _ ",
                                "|_ |_ |_ |_ |_ |_ |_ |_ |_ ",
                                "|_||_||_||_||_||_||_||_||_|"
};

const Display s_displayAll7 = { " _  _  _  _  _  _  _  _  _ ",
                                "  |  |  |  |  |  |  |  |  |",
                                "  |  |  |  |  |  |  |  |  |"
};

const Display s_displayAll8 = { " _  _  _  _  _  _  _  _  _ ",
                                "|_||_||_||_||_||_||_||_||_|",
                                "|_||_||_||_||_||_||_||_||_|"
};

const Display s_displayAll9 = { " _  _  _  _  _  _  _  _  _ ",
                                "|_||_||_||_||_||_||_||_||_|",
                                " _| _| _| _| _| _| _| _| _|"
};

const Display s_display123456789 = { "    _  _     _  _  _  _  _ ",
                                     "  | _| _||_||_ |_   ||_||_|",
                                     "  ||_  _|  | _||_|  ||_| _|"
};

/*
 *test list
 *1) check strings with single digit 0
 *2) check strings with single digit 1
 *...
 *10) check strings with single digit 9
 *11) check incorrect symbol
 *11) check 9 similar symbols
 *12) check 9 random symbols
 *13) acceptance test
 */

int ConvertDigit(const Digit &digit)
{
    std::string high = digit.lines[0];
    std::string mid = digit.lines[1];
    std::string low = digit.lines[2];

    int mask = high.at(1) == '_' ? 1 : 0;
    mask += mid.at(0) == '|' ? 2 : 0;
    mask += mid.at(1) == '_' ? 4 : 0;
    mask += mid.at(2) == '|' ? 8 : 0;
    mask += low.at(0) == '|' ? 16 : 0;
    mask += low.at(1) == '_' ? 32 : 0;

    // 1 - 001000 - 8
    // 2 - 111101 - 61
    // 3 - 101101 - 45
    // 4 - 001110 - 14
    // 5 - 100111 - 39
    // 6 - 110111 - 55
    // 7 - 001001 - 9
    // 8 - 111111 - 63
    // 9 - 101111 - 47
    // 0 - 111011 - 59

    switch(mask)
    {
    case 8:
        return 1;
    case 61:
        return 2;
    case 45:
        return 3;
    case 14:
        return 4;
    case 39:
        return 5;
    case 55:
        return 6;
    case 9:
        return 7;
    case 63:
        return 8;
    case 47:
        return 9;
    case 59:
        return 0;

    default:
        throw std::runtime_error("Unknown symbol found");
    }
}

int ConvertNumber(const Display &number)
{
    int result = 0;
    for(int i = 0; i < g_digitsOnDisplay; ++i)
    {
        int position = i * g_digitLen;
        int multiplier = std::pow(10, g_digitsOnDisplay - i - 1);
        result += multiplier * ConvertDigit({std::string(number.lines[0].c_str() + position),
                                             std::string(number.lines[1].c_str() + position),
                                             std::string(number.lines[2].c_str() + position)});
    }
    return result;
}


TEST(BankOCR, CheckDigitZero)
{
    ASSERT_EQ(0, ConvertDigit(s_digit0));
}

TEST(BankOCR, CheckDigitOne)
{
    ASSERT_EQ(1, ConvertDigit(s_digit1));
}

TEST(BankOCR, CheckDigitTwo)
{
    ASSERT_EQ(2, ConvertDigit(s_digit2));
}

TEST(BankOCR, CheckDigitThree)
{
    ASSERT_EQ(3, ConvertDigit(s_digit3));
}

TEST(BankOCR, CheckDigitFour)
{
    ASSERT_EQ(4, ConvertDigit(s_digit4));
}

TEST(BankOCR, CheckDigitFive)
{
    ASSERT_EQ(5, ConvertDigit(s_digit5));
}

TEST(BankOCR, CheckDigitSix)
{
    ASSERT_EQ(6, ConvertDigit(s_digit6));
}

TEST(BankOCR, CheckDigitSeven)
{
    ASSERT_EQ(7, ConvertDigit(s_digit7));
}

TEST(BankOCR, CheckDigitEight)
{
    ASSERT_EQ(8, ConvertDigit(s_digit8));
}

TEST(BankOCR, CheckDigitNine)
{
    ASSERT_EQ(9, ConvertDigit(s_digit9));
}

TEST(BankOCR, CheckIncorectDigits)
{
    EXPECT_THROW(ConvertDigit(s_incorrectDigit1), std::runtime_error);
    EXPECT_THROW(ConvertDigit(s_incorrectDigit2), std::runtime_error);
    EXPECT_THROW(ConvertDigit(s_incorrectDigit3), std::runtime_error);
}


TEST(BankOCR, CheckNumberAll0)
{
    ASSERT_EQ(000000000, ConvertNumber(s_displayAll0));
}

TEST(BankOCR, CheckNumberAll1)
{
    ASSERT_EQ(111111111, ConvertNumber(s_displayAll1));
}

TEST(BankOCR, CheckNumberAll2)
{
    ASSERT_EQ(222222222, ConvertNumber(s_displayAll2));
}

TEST(BankOCR, CheckNumberAll3)
{
    ASSERT_EQ(333333333, ConvertNumber(s_displayAll3));
}

TEST(BankOCR, CheckNumberAll4)
{
    ASSERT_EQ(444444444, ConvertNumber(s_displayAll4));
}

TEST(BankOCR, CheckNumberAll5)
{
    ASSERT_EQ(555555555, ConvertNumber(s_displayAll5));
}

TEST(BankOCR, CheckNumberAll6)
{
    ASSERT_EQ(666666666, ConvertNumber(s_displayAll6));
}

TEST(BankOCR, CheckNumberAll7)
{
    ASSERT_EQ(777777777, ConvertNumber(s_displayAll7));
}

TEST(BankOCR, CheckNumberAll8)
{
    ASSERT_EQ(888888888, ConvertNumber(s_displayAll8));
}

TEST(BankOCR, CheckNumberAll9)
{
    ASSERT_EQ(999999999, ConvertNumber(s_displayAll9));
}

TEST(BankOCR, CheckNumberAll123456789)
{
    ASSERT_EQ(123456789, ConvertNumber(s_display123456789));
}
