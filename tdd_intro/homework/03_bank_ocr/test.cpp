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


/*
 * - Parse digit (test for each 1..9)
 * - Wrong digit
 * - Get line
 * - Wrong line
 * - Get cell
 * - Wrong cell
 * - Get numbers
 * - Aceptance
 */

const std::string ZERO_DIGIT = " _ | ||_|";
const std::string ONE_DIGIT = "     |  |";
const std::string TWO_DIGIT = " _  _||_ ";
const std::string THREE_DIGIT = " _  _| _|";
const std::string FOUR_DIGIT = "   |_|  |";
const std::string FIVE_DIGIT = " _ |_  _|";
const std::string SIX_DIGIT = " _ |_ |_|";
const std::string SEVEN_DIGIT = " _   |  |";
const std::string EIGHT_DIGIT = " _ |_||_|";
const std::string NINE_DIGIT = " _ |_| _|";

const unsigned int DIGIT_WIDTH = 3;
const unsigned int DIGIT_FIRST_LINE_INDEX = 0;
const unsigned int DIGIT_SECOND_LINE_INDEX = 27;
const unsigned int DIGIT_THIRD_LINE_INDEX = 54;

std::string ParseNumberCell(const std::string &str)
{
    if (str == ZERO_DIGIT) return "0";
    if (str == ONE_DIGIT) return "1";
    if (str == TWO_DIGIT) return "2";
    if (str == THREE_DIGIT) return "3";
    if (str == FOUR_DIGIT) return "4";
    if (str == FIVE_DIGIT) return "5";
    if (str == SIX_DIGIT) return "6";
    if (str == SEVEN_DIGIT) return "7";
    if (str == EIGHT_DIGIT) return "8";
    if (str == NINE_DIGIT) return "9";

    return "";
}

std::string GetDigitCell(const std::string &str)
{
    std::string number = str.substr(DIGIT_FIRST_LINE_INDEX, DIGIT_WIDTH);
    number += str.substr(DIGIT_SECOND_LINE_INDEX, DIGIT_WIDTH);
    number += str.substr(DIGIT_THIRD_LINE_INDEX, DIGIT_WIDTH);

    return number;
}

TEST(BankOcr, MachineDigitToString0)
{
    ASSERT_EQ("0", ParseNumberCell(ZERO_DIGIT));
}

TEST(BankOcr, MachineWrongDigitToString)
{
    ASSERT_EQ("", ParseNumberCell("_---__--"));
}

TEST(BankOcr, MachineDigitToString1)
{
    ASSERT_EQ("1", ParseNumberCell(ONE_DIGIT));
}

TEST(BankOcr, MachineDigitToString2)
{
    ASSERT_EQ("2", ParseNumberCell(TWO_DIGIT));
}

TEST(BankOcr, MachineDigitToString3)
{
    ASSERT_EQ("3", ParseNumberCell(THREE_DIGIT));
}

TEST(BankOcr, MachineDigitToString4)
{
    ASSERT_EQ("4", ParseNumberCell(FOUR_DIGIT));
}

TEST(BankOcr, MachineDigitToString5)
{
    ASSERT_EQ("5", ParseNumberCell(FIVE_DIGIT));
}

TEST(BankOcr, MachineDigitToString6)
{
    ASSERT_EQ("6", ParseNumberCell(SIX_DIGIT));
}

TEST(BankOcr, MachineDigitToString7)
{
    ASSERT_EQ("7", ParseNumberCell(SEVEN_DIGIT));
}

TEST(BankOcr, MachineDigitToString8)
{
    ASSERT_EQ("8", ParseNumberCell(EIGHT_DIGIT));
}

TEST(BankOcr, MachineDigitToString9)
{
    ASSERT_EQ("9", ParseNumberCell(NINE_DIGIT));
}

TEST(BankOcr, GetFirstLineDigitZero)
{
    ASSERT_EQ(ZERO_DIGIT, GetDigitCell(" _  _  _  _  _  _  _  _  _ | || || || || || || || || ||_||_||_||_||_||_||_||_||_|"));
}

TEST(BankOcr, GetFirstLineDigitOne)
{
    ASSERT_EQ(ONE_DIGIT, GetDigitCell("                             |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |"));
}
