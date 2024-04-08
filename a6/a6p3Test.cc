#include <string>
#include "gtest/gtest.h"
#include "a6p3.h"

using namespace std;

// By default this file contains copies of the Marmoset tests in a6p3c.
// Currently they get 70% coverage on our solution. To pass the a6p3t coverage
// test you will need to augment them so that they get full coverage (100%
// lines executed).

// Note: The provided powerset and addChar functions were moved to another file
// in the solution on Marmoset, so you don't have to worry about covering them
// in a6p3t. Just focus on the two scabbleValue overloads and bestScrabbleWord

TEST(scrabbleValueCharPub, testAFewChars)
{
    EXPECT_EQ(scrabbleValue('a'), 1);
    EXPECT_EQ(scrabbleValue('b'), 3);
    EXPECT_EQ(scrabbleValue('c'), 3);
}

TEST(scrabbleValueCharPub, testNonLetterCharacterGivesCorrectDeath)
{
    EXPECT_DEATH(scrabbleValue('1'), "Error: Received non-alphabetical character \'1\'");
}

TEST(scrabbleValueCharNew, testAFewMoreChars)
{
    EXPECT_EQ(scrabbleValue('A'), 1);
    EXPECT_EQ(scrabbleValue('d'), 2);
    EXPECT_EQ(scrabbleValue('f'), 4);
    EXPECT_EQ(scrabbleValue('k'), 5);
    EXPECT_EQ(scrabbleValue('j'), 8);
    EXPECT_EQ(scrabbleValue('q'), 10);
}

TEST(scrabbleValueStringPub, testEmptyStringHasValueZero)
{
    EXPECT_EQ(scrabbleValue(""), 0);
}

TEST(scrabbleValueStringPub, testNonLetterCharacterGivesCorrectDeath)
{
    EXPECT_DEATH(scrabbleValue("2"), "Error: Received non-alphabetical character \'2\'");
}

TEST(scrabbleValueStringNew, testStringGivesCorrectValue)
{
    EXPECT_EQ(scrabbleValue("qUiRkS"), 19);
}

TEST(bestScrabbleWordPub, bestWordThatCanBeMadeFromNothingIsNothing)
{
    EXPECT_EQ(bestScrabbleWord(""), "");
}

TEST(bestScrabbleWordPub, testNonLetterCharacterGivesCorrectDeath)
{
    EXPECT_DEATH(bestScrabbleWord("3"), "Error: Received non-alphabetical character \'3\'");
}

TEST(bestScrabbleWordNew, bestWordThatCanBeMadeFromAllLetters)
{
    EXPECT_EQ(bestScrabbleWord("abC"), "Cab");
}

TEST(bestScrabbleWordNew, bestWordThatCanBeMadeFromSubsetOfLetters)
{
    EXPECT_EQ(bestScrabbleWord("abCX"), "aX");
}

TEST(bestScrabbleWordNew, noWordCanBeMadeFromLettersReturnsNothing)
{
    EXPECT_EQ(bestScrabbleWord("xy"), "");
}