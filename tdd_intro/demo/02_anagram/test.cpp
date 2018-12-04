/*
Given a word and a list of possible anagrams, select the correct sublist.

Given "listen" and a list of candidates like "enlists" "google" "inlets" "banana" the program should return a list containing "inlets".

_from http://exercism.io/_
*/
#include <gtest/gtest.h>
typedef std::vector<std::string> strings;

bool IsAnagramPresent(std::string first, std::string second)
{
    std::sort(first.begin(), first.end());
    std::sort(second.begin(), second.end());

    return first == second;
}

strings ReturnAnagrams(std::string target, const strings& variants)
{
    strings anagrams;
    for (std::string variant : variants)
    {
        if (IsAnagramPresent(target, variant))
        {
            anagrams.push_back(variant);
        }
    }

    return anagrams;
}

TEST (anagrams, emptyString)
{
    EXPECT_TRUE(IsAnagramPresent("", ""));
}

TEST(anagrams, notEqualWords)
{
    EXPECT_FALSE(IsAnagramPresent("word", "lock"));
}

TEST(anagrams, anagram)
{
    EXPECT_TRUE(IsAnagramPresent("listen", "inlets"));
}

TEST(anagrams, returnEmptyString)
{
    EXPECT_EQ(strings(), ReturnAnagrams("", strings()));
}

TEST(anagrams, singleAnagram)
{
    EXPECT_EQ( strings({"inlets"}), ReturnAnagrams("listen", strings({"inlets"})));
}

TEST(anagrams, otherSignleAnagram)
{
    EXPECT_EQ( strings({"letsin"}), ReturnAnagrams("listen", strings({"letsin"})));
}

TEST(anagrams, signleNotAnagram)
{
    EXPECT_EQ( strings(), ReturnAnagrams("listen", strings({"letiin"})));
}

TEST(anagrams, multipleWordsOnaAnagram)
{
    EXPECT_EQ(strings({"inlets"}), ReturnAnagrams("listen", strings({"inlets", "google"})));
}

TEST(anagrams, multipleAnagrams)
{
    EXPECT_EQ(strings({"inlets", "inelts"}), ReturnAnagrams("listen", strings({"inlets", "inelts"})));
}

TEST(anagrams, multipleAnagramsNotInOrder)
{
    EXPECT_EQ(strings({"inelts", "inlets"}), ReturnAnagrams("listen", strings({"inlets", "inelts"})));
}
