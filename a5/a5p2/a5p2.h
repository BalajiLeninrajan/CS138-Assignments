// Don't change any of the includes
#include <string>
#include <map>
#include "gtest/gtest.h"

class LexTree
{
public:
    // Don't modify the public interface. If you change it
    // then your solution probably won't compile on Marmoset
    LexTree();
    virtual ~LexTree();
    void addWord(const std::string &s);
    bool hasWord(const std::string &s) const;
    std::string toString() const;

private:
    // Fields: You may add new fields if you'd like, but don't
    // change isWord or children since then you'll break the
    // Marmoset whitebox tests
    bool isWord;
    std::map<char, LexTree *> children;

    // Private Methods: The is isValid method needs too stay
    // as-is (since Marmoset needs to be able to call it),
    // but feel free to add some helper functions here if you
    // want.
    bool isValid() const;
    // void yourFunction(std::string example) const;
    // ... etc ...
    std::string toString_helper(std::string current) const;

    // Friends
    FRIEND_TEST(defaultCtorPub, defaultCtorShouldMakeEmptyLex);
    FRIEND_TEST(isValidPub, emptyTreeShouldBeValid);
    FRIEND_TEST(isValidPub, checkAllLowerCase1);
    FRIEND_TEST(isValidPub, checkAllLowerCase2);
    FRIEND_TEST(isValidPub, leafNodeShouldBeWords);
    FRIEND_TEST(addWordPub, addAWordAndCheckNodes);
    FRIEND_TEST(hasWordPub, addAWordAndCheckIt);
    FRIEND_TEST(toStringPub, addOneWordAndPrint);
    FRIEND_TEST(toStringPub, addTwoWordsAndPrint);

    // FRIEND_TEST(yourWhiteboxTest, yourTestName);
    // ... etc ...
    FRIEND_TEST(toStringNew, addTwoWordsAndPrint);

    // When you make new whitebox LexTree test cases you will need
    // to add them as friends here so that they can access LexTree's
    // private members.
    // On the other hand, if you make new blackbox test cases which
    // only use the public API then you should NOT make them friends
    // with the LexTree class.
};
