#include "a3p2.h"
#include "gtest/gtest.h"
#include <iostream>

using namespace std;

/* ************************************************************** */
/* Chunky Stack Validity                                          */
/* ************************************************************** */

TEST(StackForm, ChunkSizeBelowZero) {
    Stack s;
    s.chunkSize = -1;
    EXPECT_DEATH(isValidStack(s), "");
}

TEST(StackForm, ChunkSizeZero) {
    Stack s;
    s.chunkSize = 0;
    EXPECT_DEATH(isValidStack(s), "");
}

TEST(StackForm, TopEltGreaterThanChunkSize) {
    Stack s;
    s.chunkSize = 1;
    s.topElt = 2;
    EXPECT_DEATH(isValidStack(s), "");
}

TEST(StackForm, EmptyStackWithBadTopElt) {
    Stack s;
    s.firstChunk = nullptr;
    s.topElt = 1; // this should be -1 for an empty stack
    s.chunkSize = 10;
    EXPECT_TRUE(isEmpty(s)); 
    EXPECT_DEATH(isValidStack(s), "");
}

TEST(StackForm, StackCannotStoreSpecialUnusedSlotValue) {
    Stack s;
    initStack(1, s);
    s.firstChunk = createNewNodeChunk(1);
    s.topElt = 0;
    s.firstChunk->val[0] = "alpha";
    EXPECT_FALSE(isEmpty(s)); 
    EXPECT_TRUE(isValidStack(s));
    // cout << "wellformed so far ;)" << endl;
    // wellformed so far, now mess it up
    s.firstChunk->val[0] = UNUSED_SLOT;
    EXPECT_DEATH(isValidStack(s), "");
    delete[] s.firstChunk->val;
    delete s.firstChunk;
}

TEST(StackForm, UnusedStackSlotsShouldNotHaveGhostValues) {
    Stack s;
    initStack(5, s);
    s.firstChunk = createNewNodeChunk(5);
    s.topElt = 2;
    s.firstChunk->val[s.topElt+1] = "ghost value should not be here";
    EXPECT_FALSE(isEmpty(s)); 
    EXPECT_DEATH(isValidStack(s), "");
    delete[] s.firstChunk->val;
    delete s.firstChunk;
}

TEST(StackForm, SubsequentChunkShouldNotHaveUnusedSlots) {
    Stack s;
    initStack(1, s);
    s.topElt = 0;
    s.firstChunk = createNewNodeChunk(1);
    s.firstChunk->val[0] = "beta";
    s.firstChunk->next = createNewNodeChunk(1);
    s.firstChunk->next->val[0] = "alpha";
    EXPECT_FALSE(isEmpty(s)); 
    EXPECT_TRUE(isValidStack(s));
    // wellformed so far
    // now we break it
    s.firstChunk->next->val[0] = UNUSED_SLOT;
    EXPECT_DEATH(isValidStack(s), "");
    delete[] s.firstChunk->next->val;
    delete s.firstChunk->next;
    delete[] s.firstChunk->val;
    delete s.firstChunk;
}


/* ************************************************************** */
/* End-to-end testing                                             */
/* ************************************************************** */

TEST(EndToEnd, GivenOneItemIsPushedTheSameItemExpectedAtTop) {
    Stack s;
    initStack (3,s);
    
    string expected = "alpha";
    push(expected, s);
    EXPECT_EQ(expected, top(s));

    nuke(s);
}

TEST(EndToEnd, EmptyStackAllChecks) {
    Stack s;
    initStack (3,s);
    
    EXPECT_EQ(0,size(s));

    nuke(s);
    EXPECT_EQ(0,size(s));
}

TEST(EndToEnd, GivenTwoPushedElementsTheSecondItemExpectedAtTop) {
    Stack s;
    initStack (3,s);
    push("alpha", s);

    string expected = "beta";
    push(expected, s);

    EXPECT_EQ(2,size(s));

    EXPECT_EQ(expected, top(s));

    nuke(s);
}

TEST(EndToEnd, GivenTwoPushedElementsCombinationOfTheseTwoIsExpectedFromToString) {
    Stack s;
    initStack (3,s);
    push("alpha", s);
    push("beta", s);

    string expected = "[beta, alpha]";
    EXPECT_EQ(expected, toString(s));

    nuke(s);
}

TEST(EndToEnd, GivenTwoPushedElementsWhenPopIsInvokedSecondOneExpectedToRemain) {
    Stack s;
    initStack (3,s);
    push("alpha", s);
    push("beta", s);
    pop(s);

    string expected = "alpha";
    EXPECT_EQ(expected, top(s));

    nuke(s);
}

TEST(EndToEnd, GivenTwoPushedElementsTheSizeOfTwoIsExpected) {
    Stack s;
    initStack (3,s);

    push("alpha", s);
    push("beta", s);

    EXPECT_EQ(2, size(s));

    nuke(s);
}

TEST(EndToEnd, GivenTwoPushedElementsWhenSwapIsInvokedSwappedItemsExpectedFromToString) {
    Stack s;
    initStack (3,s);

    push("alpha", s);
    push("beta", s);

    EXPECT_EQ(2,size(s));

    swap(s);

    string expected = "[alpha, beta]";
    EXPECT_EQ(expected, toString(s));

    nuke(s);
}

TEST(EndToEnd, GivenThreeOfThreeIsInvokedSizeExpectedFullNukeTwice) {
    Stack s;
    initStack (3,s);

    push("alpha", s);
    push("beta", s);
    push("ceta", s);

    EXPECT_EQ(3, size(s));

    nuke(s);
    nuke(s);
}

TEST(EndToEnd, GivenTenOfThreeIsInvokedSizeExpectedFull) {
    Stack s;
    initStack (3,s);

    push("j", s);
    push("i", s);
    push("h", s);
    push("g", s);
    push("f", s);
    push("e", s);
    push("d", s);
    push("c", s);
    push("b", s);
    push("a", s);

    EXPECT_EQ(10, size(s));

    EXPECT_EQ("[a, b, c, d, e, f, g, h, i, j]",toString(s));

    swap(s);    // try swapping at the top (we would have to swap over two)

    EXPECT_EQ("[b, a, c, d, e, f, g, h, i, j]",toString(s));

    pop(s);
    pop(s);
    pop(s);
    pop(s);
    pop(s);
    pop(s);
    pop(s);
    pop(s);
    pop(s);
    pop(s);

    EXPECT_EQ(0, size(s));

    nuke(s);
}



TEST(EndToEnd, PopEmptyExpectFail) {
    Stack s;
    initStack (3,s);

    EXPECT_DEATH(pop(s),"");
}

TEST(EndToEnd, SwapEmptyExpectFail) {
    Stack s;
    initStack (3,s);

    EXPECT_DEATH(swap(s),"");
}


TEST(EndToEnd, AddIllegal) {
    Stack s;
    initStack (3,s);

    EXPECT_DEATH(push(UNUSED_SLOT,s),"");
}

// public test cases
TEST(StackForm, FChunkSizeAboveZero) {
    Stack s;
    s.chunkSize = -1;
    EXPECT_DEATH(isValidStack(s), "");
}

TEST(StackForm, FTopEltGreaterThanChunkSize) {
    Stack s;
    s.chunkSize = 1;
    s.topElt = 2;
    EXPECT_DEATH(isValidStack(s), "");
}

TEST(StackForm, FEmptyStackWithBadTopElt) {
    Stack s;
    s.firstChunk = nullptr;
    s.topElt = 1; // this should be -1 for an empty stack
    EXPECT_TRUE(isEmpty(s)); 
    EXPECT_DEATH(isValidStack(s), "");
}

TEST(StackForm, FStackCannotStoreSpecialUnusedSlotValue) {
    Stack s;
    initStack(1, s);
    s.firstChunk = createNewNodeChunk(1);
    s.topElt = 0;
    s.firstChunk->val[0] = "alpha";
    EXPECT_FALSE(isEmpty(s)); 
    EXPECT_TRUE(isValidStack(s));
    // wellformed so far, now mess it up
    s.firstChunk->val[0] = UNUSED_SLOT;
    EXPECT_DEATH(isValidStack(s), "");
    delete[] s.firstChunk->val;
    delete s.firstChunk;
}

TEST(StackForm, FUnusedStackSlotsShouldNotHaveGhostValues) {
    Stack s;
    initStack(5, s);
    s.firstChunk = createNewNodeChunk(5);
    s.topElt = 2;
    s.firstChunk->val[s.topElt+1] = "ghost value should not be here";
    EXPECT_FALSE(isEmpty(s)); 
    EXPECT_DEATH(isValidStack(s), "");
    delete[] s.firstChunk->val;
    delete s.firstChunk;
}

TEST(StackForm, FSubsequentChunkShouldNotHaveUnusedSlots) {
    Stack s;
    initStack(1, s);
    s.topElt = 0;
    s.firstChunk = createNewNodeChunk(1);
    s.firstChunk->val[0] = "beta";
    s.firstChunk->next = createNewNodeChunk(1);
    s.firstChunk->next->val[0] = "alpha";
    EXPECT_FALSE(isEmpty(s)); 
    EXPECT_TRUE(isValidStack(s));
    // wellformed so far
    // now we break it
    s.firstChunk->next->val[0] = UNUSED_SLOT;
    EXPECT_DEATH(isValidStack(s), "");
    delete[] s.firstChunk->next->val;
    delete s.firstChunk->next;
    delete[] s.firstChunk->val;
    delete s.firstChunk;
}


// This tests was given to you in a3p2Test.cc
TEST(PopPub, FGivenTwoPushedElementsWhenPopIsInvokedSecondOneExpectedToRemain) {
    Stack s;
    initStack (3,s);
    // These lines were changed to avoid using push()
    s.firstChunk = createNewNodeChunk(3);
    s.firstChunk->val[0] = "alpha";
    s.firstChunk->val[1] = "beta";
    s.topElt = 1;

    pop(s);

    string expected = "alpha";
    // This line was changed to avoid using top()
    EXPECT_EQ(expected, s.firstChunk->val[s.topElt]);

    // Marmoset uses delete instead of nuke in case your nuke function is broken
    delete [] s.firstChunk->val;
    delete s.firstChunk;
}

// This test is new, feel free to add it to your test file
TEST(PopPub, FGivenEmptyStackWhenPopIsInvokedDeathExpected) {
    Stack s;
    initStack (10,s);
    EXPECT_DEATH(pop(s), "");
}


// These tests are new, feel free to add them to your test file
TEST(ToStringPub, GivenEmptyStackWhenToStringIsInvokedAnEmptyStringIsExpected) {
    Stack s;
    initStack(10,s);

    string expected = "[]";
    EXPECT_EQ(expected, toString(s));
}

TEST(ToStringPub, GivenSingleElementStackWhenToStringIsInvokedItemExpectedInTheString) {
    Stack s;
    initStack(10,s);
    s.firstChunk = createNewNodeChunk(10);
    s.firstChunk->val[0] = "alpha";
    s.topElt = 0;

    string expected = "[alpha]";
    EXPECT_EQ(expected, toString(s));

    delete [] s.firstChunk->val;
    delete s.firstChunk;
}


TEST(TopPub, GivenEmptyStackWhenTopIsInvokedDeathExpected) {
    Stack s;
    initStack (10,s);
    EXPECT_DEATH(top(s), "");
}

TEST(SwapPub, GivenTwoPushedElementsWhenSwapIsInvokedSwappedItemsExpected) {
    Stack s;
    initStack (3,s);
    s.firstChunk = createNewNodeChunk(3);
    s.firstChunk->val[0] = "alpha";
    s.firstChunk->val[1] = "beta";
    s.topElt = 1;

    swap(s);

    EXPECT_EQ("alpha", s.firstChunk->val[s.topElt]);
    EXPECT_EQ("beta", s.firstChunk->val[s.topElt - 1]);

    swap(s);

    EXPECT_EQ("beta", s.firstChunk->val[s.topElt]);
    EXPECT_EQ("alpha", s.firstChunk->val[s.topElt - 1]);

    delete [] s.firstChunk->val;
    delete s.firstChunk;
}

TEST(SwapPub, GivenSingleElementStackWhenSwapIsInvokedExpectDeath) {
    Stack s;
    initStack (3,s);
    s.firstChunk = createNewNodeChunk(3);
    s.firstChunk->val[0] = "alpha";
    s.topElt = 0;

    EXPECT_DEATH(swap(s), "");

    delete [] s.firstChunk->val;
    delete s.firstChunk;
}

TEST(SwapPub, GivenEmptyStackWhenSwapIsInvokedExpectDeath) {
    Stack s;
    initStack (3,s);
    EXPECT_DEATH(swap(s), "");
}