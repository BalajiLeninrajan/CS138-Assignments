#include "a5p2.h"
#include "gtest/gtest.h"

using namespace std;

/* ************************************************************** */
/* Tests for Assignment 5 Part 2                                  */
/* ************************************************************** */
// By default this file contains exact copies of all the Marmoset
// public tests in a5p2c.

// IMPORTANT: The recursive nature of our solution means that it
// contains very few conditional jumps. This means that it is very
// easy to achieve full coverage for this part. In fact, the
// provided tests already get full coverage on our solution! Because
// of this a5p2t is not worth any marks, but you can still use it to
// check the correctness of your own tests on our solution.

// WARNING: Every Marmoset test will use your default constructor
// AND your destructor. Now that we have transitioned to using
// classes and OOP this is kind-of unavoidable. Neither of these
// should be too hard to write, but be careful! The stakes are much
// higher with these two.

TEST(defaultCtorPub, defaultCtorShouldMakeEmptyLex)
{
    LexTree *lt = new LexTree{};
    EXPECT_FALSE(lt->isWord);
    EXPECT_TRUE(lt->children.empty());
    delete lt;
}

TEST(isValidPub, emptyTreeShouldBeValid)
{
    LexTree *lt = new LexTree{};
    EXPECT_TRUE(lt->isValid());
    delete lt;
}

// All key should be in lowercase
TEST(isValidPub, checkAllLowerCase1)
{
    LexTree *lt = new LexTree{};
    lt->children['T'] = new LexTree{};
    EXPECT_DEATH(lt->isValid(), "");
    delete lt;
}

TEST(isValidPub, checkAllLowerCase2)
{
    LexTree *lt = new LexTree{};
    lt->children['h'] = new LexTree{};
    lt->children['h']->children['E'] = new LexTree{};
    EXPECT_DEATH(lt->isValid(), "");
    delete lt;
}

// All leaf nodes should have isWord = true.
// Food for thought: Can you figure out why?
TEST(isValidPub, leafNodeShouldBeWords)
{
    LexTree *lt = new LexTree{};
    lt->addWord("hi");
    lt->children['h']->children['i']->isWord = false;
    EXPECT_DEATH(lt->isValid(), "");
    delete lt;
}

// Add the word "to" and check nodes of the lex
// the first node should only have 't' in its children
// the node pointed to by 't' should only have 'o' in its children
// the node pointed to by 'o' should have an empty map as its children
TEST(addWordPub, addAWordAndCheckNodes)
{
    LexTree *lt = new LexTree{};
    lt->addWord("to");
    // check
    ASSERT_NE(lt->children.find('t'), lt->children.end());
    EXPECT_EQ(lt->children.size(), 1);
    ASSERT_NE(lt->children.at('t')->children.find('o'), lt->children.at('t')->children.end());
    EXPECT_EQ(lt->children.at('t')->children.size(), 1);
    ASSERT_EQ(lt->children.at('t')->children.at('o')->children.size(), 0);
    delete lt;
}

TEST(hasWordPub, addAWordAndCheckIt)
{
    LexTree *lt = new LexTree{};

    // Manually create a LexTree containing the word "to"
    lt->children.emplace('t', new LexTree{});
    lt->children.at('t')->children.emplace('o', new LexTree{});
    lt->children.at('t')->children.at('o')->isWord = true;

    ASSERT_TRUE(lt->hasWord("to"));
    ASSERT_FALSE(lt->hasWord("t"));
    ASSERT_FALSE(lt->hasWord("o"));
    ASSERT_FALSE(lt->hasWord(""));
    delete lt;
}

// Notice how this test only uses the public API of LexTree? This means
// we don't need to (and shouldn't) make it a friend of LexTree.
TEST(toStringPub, printEmptyLex)
{
    LexTree *lt = new LexTree{};
    string expected_result = "";
    ASSERT_EQ(lt->toString(), expected_result);
    delete lt;
}

TEST(toStringPub, addOneWordAndPrint)
{
    LexTree *lt = new LexTree{};

    // Add the word "man"
    lt->children.emplace('m', new LexTree{});
    lt->children.at('m')->children.emplace('a', new LexTree{});
    lt->children.at('m')->children.at('a')->children.emplace('n', new LexTree{});
    lt->children.at('m')->children.at('a')->children.at('n')->isWord = true;

    string expected_result = "man\n";
    ASSERT_EQ(lt->toString(), expected_result);
    delete lt;
}

TEST(toStringPub, addTwoWordsAndPrint)
{
    LexTree *lt = new LexTree{};

    // Manually add the words "super" and "man"

    // Add the word "super"
    lt->children.emplace('s', new LexTree{});
    lt->children.at('s')->children.emplace('u', new LexTree{});
    lt->children.at('s')->children.at('u')->children.emplace('p', new LexTree{});
    lt->children.at('s')->children.at('u')->children.at('p')->children.emplace('e', new LexTree{});
    lt->children.at('s')->children.at('u')->children.at('p')->children.at('e')->children.emplace('r', new LexTree{});
    lt->children.at('s')->children.at('u')->children.at('p')->children.at('e')->children.at('r')->isWord = true;

    // Add the word "man"
    lt->children.emplace('m', new LexTree{});
    lt->children.at('m')->children.emplace('a', new LexTree{});
    lt->children.at('m')->children.at('a')->children.emplace('n', new LexTree{});
    lt->children.at('m')->children.at('a')->children.at('n')->isWord = true;

    string expected_result = "man\n"
                             "super\n";
    ASSERT_EQ(lt->toString(), expected_result);
    delete lt;
}

TEST(toStringNew, addTwoWordsAndPrint)
{
    LexTree *lt = new LexTree{};

    // Manually add the words "super" and "man"

    // Add the words "a, at, ate"
    lt->children.emplace('a', new LexTree{});
    lt->children.at('a')->isWord = true;
    lt->children.at('a')->children.emplace('t', new LexTree{});
    lt->children.at('a')->children.at('t')->isWord = true;
    lt->children.at('a')->children.at('t')->children.emplace('e', new LexTree{});
    lt->children.at('a')->children.at('t')->children.at('e')->isWord = true;

    // Add the words "as, ass, ask, asset"
    lt->children.at('a')->children.emplace('s', new LexTree{});
    lt->children.at('a')->children.at('s')->children.emplace('s', new LexTree{});
    lt->children.at('a')->children.at('s')->children.at('s')->isWord = true;
    lt->children.at('a')->children.at('s')->children.emplace('k', new LexTree{});
    lt->children.at('a')->children.at('s')->children.at('k')->isWord = true;
    lt->children.at('a')->children.at('s')->children.at('s')->children.emplace('e', new LexTree{});
    lt->children.at('a')->children.at('s')->children.at('s')->children.at('e')->children.emplace('t', new LexTree{});
    lt->children.at('a')->children.at('s')->children.at('s')->children.at('e')->children.at('t')->isWord = true;

    // Add the word "axe"
    lt->children.at('a')->children.emplace('x', new LexTree{});
    lt->children.at('a')->children.at('x')->children.emplace('e', new LexTree{});
    lt->children.at('a')->children.at('x')->children.at('e')->isWord = true;

    string expected_result = "a\n"
                             "ask\n"
                             "ass\n"
                             "asset\n"
                             "at\n"
                             "ate\n"
                             "axe\n";
    ASSERT_EQ(lt->toString(), expected_result);
    delete lt;
}