/*
Bob answers 'Sure.' if you ask him a question. (? in the end)

He answers 'Whoa, chill out!' if you yell at him. (! in the end)

He says 'Fine. Be that way!' if you address him without actually saying anything.

He answers 'Whatever.' to anything else.
*/
#include <gtest/gtest.h>
#include <string>

const std::string g_tellBobAnswer = "Sure";
const std::string g_yellBobAnswer = "Whoa, chill out!";
const std::string g_emptyBobAnswer = "Fine. Be that way!";
const std::string g_defaultBobAnswer = "Whatever.";

std::string CallBob(const std::string& str)
{
    if (str.empty())
    {
        return g_emptyBobAnswer;
    }
    if (str.back() == '!')
    {
        return g_yellBobAnswer;
    }
    else if (str.back() == '?')
    {
        return g_tellBobAnswer;
    }

    return g_defaultBobAnswer;
}

TEST(bob, AnswerSureOnQuestion)
{
    ASSERT_EQ(g_tellBobAnswer, CallBob("Are you ok?"));
}

TEST(bob, AnswerChillOnYell)
{
    ASSERT_EQ(g_yellBobAnswer, CallBob("Yell!!!!"));
}

TEST(bob, AnswerOnEmptyString)
{
    ASSERT_EQ(g_emptyBobAnswer, CallBob(""));
}

TEST(bob, AnswerOnAnythingElse)
{
    ASSERT_EQ(g_defaultBobAnswer, CallBob("Anything else"));
}
