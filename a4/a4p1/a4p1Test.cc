#include "gtest/gtest.h"
#include "a4p1.h"

using namespace std;

/* ************************************************************** */
/* Tests for Assignment 4 Part 1                                  */
/* ************************************************************** */
// By default this file contains exact copies of all the Marmoset
// public tests in a4p1c.

// Currently these tests achieve 90% coverage on the staff solution.
// To pass a4p1t you will need to augment them to achieve at lest
// 95% coverage on our solution (though, as usual, 100% coverage is
// possible). Note that the Queue functions in the staff solution
// were moved to a separate file, so you don't need to worry about
// covering them with your tests. Just focus on testing the PQ
// functions.

// Because these tests are for Marmoset, each test can only call the
// function it is specifically meant to run. This makes them large
// and messy. The tests you write don't need to do this. Don't waste
// your time building and destroying linked lists manually. If you
// want to test PQ_first, PQ_leave, PQ_size, etc. use your PQ_enter
// and PQ_nuke functions to create and destroy your testing PQs.

TEST(isEmptyPub, expectEmptyPQIsEmpty)
{
    PQ pq;
    PQ_init(pq);
    EXPECT_TRUE(PQ_isEmpty(pq));
}

TEST(isEmptyPub, expectNonEmptyPQIsNotEmpty)
{
    // Make the PQ
    Queue priority1;
    priority1.first = priority1.last = new Qnode{"test", nullptr};
    PQ pq = new PQnode{1, priority1, nullptr};

    // Test PQ_isEmpty
    EXPECT_FALSE(PQ_isEmpty(pq));

    // Cleanup
    delete priority1.first;
    delete pq;
}

TEST(enterPub, enterThreeElementsExpectCorrectContents)
{
    // Make the PQ
    PQ pq;
    PQ_init(pq);
    PQ_enter(pq, "a", 2);
    PQ_enter(pq, "b", 1);
    PQ_enter(pq, "c", 4);

    // Check the first PQnode
    ASSERT_NE(pq, nullptr);
    EXPECT_EQ(pq->priority, 1);
    EXPECT_EQ(pq->q.first, pq->q.last);
    ASSERT_NE(pq->q.first, nullptr);
    EXPECT_EQ(pq->q.first->val, "b");
    EXPECT_EQ(pq->q.first->next, nullptr);
    ASSERT_NE(pq->next, nullptr);

    // Check the second PQnode
    PQ pq2 = pq->next;
    EXPECT_EQ(pq2->priority, 2);
    EXPECT_EQ(pq2->q.first, pq2->q.last);
    ASSERT_NE(pq2->q.first, nullptr);
    EXPECT_EQ(pq2->q.first->val, "a");
    EXPECT_EQ(pq2->q.first->next, nullptr);
    ASSERT_NE(pq2->next, nullptr);

    // Check the third PQnode
    PQ pq3 = pq2->next;
    EXPECT_EQ(pq3->priority, 4);
    EXPECT_EQ(pq3->q.first, pq3->q.last);
    ASSERT_NE(pq3->q.first, nullptr);
    EXPECT_EQ(pq3->q.first->val, "c");
    EXPECT_EQ(pq3->q.first->next, nullptr);
    EXPECT_EQ(pq3->next, nullptr);

    // delete the PQ manually
    delete pq3->q.first;
    delete pq3;
    delete pq2->q.first;
    delete pq2;
    delete pq->q.first;
    delete pq;
}

TEST(firstPub, givenEmptyPQExpectFirstDies)
{
    PQ pq;
    PQ_init(pq);
    EXPECT_DEATH(PQ_first(pq), "Error, priority queue is empty.");
}

TEST(firstPub, givenTheeElementPQExpectFirstGivesCorrectOutput)
{
    // Create the two Queues for the PQ
    Queue priority1;
    priority1.first = new Qnode{"alpha", new Qnode{"beta", nullptr}};
    priority1.last = priority1.first->next;
    Queue priority2;
    priority2.first = priority2.last = new Qnode{"delta", nullptr};

    // Create the PQ
    PQ pq = new PQnode{1, priority1, new PQnode{2, priority2, nullptr}};

    // Test PQ_first
    EXPECT_EQ(PQ_first(pq), "alpha");

    // Clean up
    delete pq->next;
    delete pq;
    delete priority1.first;
    delete priority1.last;
    delete priority2.first;
}

TEST(leavePub, givenEmptyPQExpectLeaveDies)
{
    PQ pq;
    PQ_init(pq);
    EXPECT_DEATH(PQ_leave(pq), "Error, priority queue is empty.");
}

TEST(leavePub, givenTheeElementPQExpectLeaveRemovesFirst)
{
    // Create the two Queues for the PQ
    Queue priority1;
    priority1.first = new Qnode{"alpha", new Qnode{"beta", nullptr}};
    priority1.last = priority1.first->next;
    Queue priority2;
    priority2.first = priority2.last = new Qnode{"delta", nullptr};

    // Create the PQ
    PQ pq = new PQnode{1, priority1, new PQnode{2, priority2, nullptr}};

    // Test PQ_leave
    PQ_leave(pq);

    // Clean up
    delete pq->next;
    delete pq;
    delete priority1.last;
    delete priority2.first;
}

TEST(sizePub, givenEmptyPQExpectSizeIsZero)
{
    PQ pq;
    PQ_init(pq);
    EXPECT_EQ(PQ_size(pq), 0);
}

TEST(sizePub, givenTheeElementPQExpectSizeIsThree)
{
    // Create the two Queues for the PQ
    Queue priority1;
    priority1.first = new Qnode{"alpha", new Qnode{"beta", nullptr}};
    priority1.last = priority1.first->next;
    Queue priority2;
    priority2.first = priority2.last = new Qnode{"delta", nullptr};

    // Create the PQ
    PQ pq = new PQnode{1, priority1, new PQnode{2, priority2, nullptr}};

    // Test PQ_size
    EXPECT_EQ(PQ_size(pq), 3);

    // Clean up
    delete pq->next;
    delete pq;
    delete priority1.first;
    delete priority1.last;
    delete priority2.first;
}

TEST(sizeByPriorityPub, givenEmptyPQExpectSizeByPriorityIsZero)
{
    PQ pq;
    PQ_init(pq);
    EXPECT_EQ(PQ_sizeByPriority(pq, 1), 0);
}

TEST(sizeByPriorityPub, givenTheeElementPQExpectSizeByPriorityIsTwo)
{
    // Create the two Queues for the PQ
    Queue priority1;
    priority1.first = new Qnode{"alpha", new Qnode{"beta", nullptr}};
    priority1.last = priority1.first->next;
    Queue priority2;
    priority2.first = priority2.last = new Qnode{"delta", nullptr};

    // Create the PQ
    PQ pq = new PQnode{1, priority1, new PQnode{2, priority2, nullptr}};

    // Test PQ_sizeByPriority
    EXPECT_EQ(PQ_sizeByPriority(pq, 1), 2);

    // Clean up
    delete pq->next;
    delete pq;
    delete priority1.first;
    delete priority1.last;
    delete priority2.first;
}

TEST(numPrioritiesPub, givenEmptyPQExpectZeroPriorities)
{
    PQ pq;
    PQ_init(pq);
    EXPECT_EQ(PQ_numPriorities(pq), 0);
}

TEST(nukePub, givenTheeElementPQExpectNukeCleansUp)
{
    // Create the two Queues for the PQ
    Queue priority1;
    priority1.first = new Qnode{"alpha", new Qnode{"beta", nullptr}};
    priority1.last = priority1.first->next;
    Queue priority2;
    priority2.first = priority2.last = new Qnode{"delta", nullptr};

    // Create the PQ
    PQ pq = new PQnode{1, priority1, new PQnode{2, priority2, nullptr}};

    // Test PQ_nuke
    PQ_nuke(pq);
    EXPECT_EQ(pq, nullptr);
}

/* ************************************************************** */
/* MORE TESTS HERE                                                */
/* ************************************************************** */

TEST(enterNew, enterOneElementExpectCorrectContents)
{
    // Make the PQ
    PQ pq;
    PQ_init(pq);
    PQ_enter(pq, "a", 1);

    // Check the first PQnode
    ASSERT_NE(pq, nullptr);
    EXPECT_EQ(pq->priority, 1);
    ASSERT_NE(pq->q.first, nullptr);
    EXPECT_EQ(pq->q.first->val, "a");
    EXPECT_EQ(pq->q.first, pq->q.last);
    EXPECT_EQ(pq->q.last->next, nullptr);
    EXPECT_EQ(pq->next, nullptr);

    // delete the PQ manually
    delete pq->q.first;
    delete pq;
}

TEST(enterNew, enterTwoElementsWithSamePriorityExpectCorrectContents)
{
    // Make the PQ
    PQ pq;
    PQ_init(pq);
    PQ_enter(pq, "a", 1);
    PQ_enter(pq, "b", 1);
    PQ_enter(pq, "c", 2);

    // Check the first PQnode
    ASSERT_NE(pq, nullptr);
    EXPECT_EQ(pq->priority, 1);
    ASSERT_NE(pq->q.first, nullptr);
    EXPECT_EQ(pq->q.first->val, "a");
    EXPECT_EQ(pq->q.first->next, pq->q.last);
    EXPECT_EQ(pq->q.last->val, "b");
    EXPECT_EQ(pq->q.last->next, nullptr);
    ASSERT_NE(pq->next, nullptr);

    // Check the second PQnode
    PQ pq2 = pq->next;
    EXPECT_EQ(pq2->priority, 2);
    EXPECT_EQ(pq2->q.first, pq2->q.last);
    ASSERT_NE(pq2->q.first, nullptr);
    EXPECT_EQ(pq2->q.first->val, "c");
    EXPECT_EQ(pq2->q.first->next, nullptr);
    EXPECT_EQ(pq2->next, nullptr);

    // delete the PQ manually
    delete pq2->q.first;
    delete pq2;
    delete pq->q.first;
    delete pq->q.last;
    delete pq;
}

TEST(enterNew, enterTwoElementsOnSecondNodeExpectCorrectContents)
{
    // Make the PQ
    PQ pq;
    PQ_init(pq);
    PQ_enter(pq, "a", 1);
    PQ_enter(pq, "b", 2);
    PQ_enter(pq, "c", 2);

    // Check the first PQnode
    ASSERT_NE(pq, nullptr);
    EXPECT_EQ(pq->priority, 1);
    EXPECT_EQ(pq->q.first, pq->q.last);
    ASSERT_NE(pq->q.first, nullptr);
    EXPECT_EQ(pq->q.first->val, "a");
    // EXPECT_EQ(pq->q.first->next, pq->q.last);
    // EXPECT_EQ(pq->q.last->val, "b");
    EXPECT_EQ(pq->q.first->next, nullptr);
    ASSERT_NE(pq->next, nullptr);

    // Check the second PQnode
    PQ pq2 = pq->next;
    EXPECT_EQ(pq2->priority, 2);
    ASSERT_NE(pq2->q.first, nullptr);
    EXPECT_EQ(pq2->q.first->next, pq2->q.last);
    EXPECT_EQ(pq2->q.first->val, "b");
    EXPECT_EQ(pq2->q.last->val, "c");
    EXPECT_EQ(pq2->q.last->next, nullptr);
    EXPECT_EQ(pq2->next, nullptr);

    // delete the PQ manually
    delete pq2->q.first;
    delete pq2->q.last;
    delete pq2;
    delete pq->q.first;
    delete pq;
}

TEST(enterNew, enterNodeInMiddleExpectCorrectContents)
{
    // Make the PQ
    PQ pq;
    PQ_init(pq);
    PQ_enter(pq, "a", 1);
    PQ_enter(pq, "b", 3);
    PQ_enter(pq, "c", 2);

    // Check the first PQnode
    ASSERT_NE(pq, nullptr);
    EXPECT_EQ(pq->priority, 1);
    EXPECT_EQ(pq->q.first, pq->q.last);
    ASSERT_NE(pq->q.first, nullptr);
    EXPECT_EQ(pq->q.first->val, "a");
    EXPECT_EQ(pq->q.first->next, nullptr);
    ASSERT_NE(pq->next, nullptr);

    // Check the second PQnode
    PQ pq2 = pq->next;
    EXPECT_EQ(pq2->priority, 2);
    EXPECT_EQ(pq2->q.first, pq2->q.last);
    ASSERT_NE(pq2->q.first, nullptr);
    EXPECT_EQ(pq2->q.first->val, "c");
    EXPECT_EQ(pq2->q.first->next, nullptr);
    ASSERT_NE(pq2->next, nullptr);

    // Check the third PQnode
    PQ pq3 = pq2->next;
    EXPECT_EQ(pq3->priority, 3);
    EXPECT_EQ(pq3->q.first, pq3->q.last);
    ASSERT_NE(pq3->q.first, nullptr);
    EXPECT_EQ(pq3->q.first->val, "b");
    EXPECT_EQ(pq3->q.first->next, nullptr);
    EXPECT_EQ(pq3->next, nullptr);

    // delete the PQ manually
    delete pq3->q.first;
    delete pq3;
    delete pq2->q.first;
    delete pq2;
    delete pq->q.first;
    delete pq;
}

TEST(leaveNew, givenOneElementExpectLeaveEmptyPQ)
{
    // Create a Queue for the PQ
    Queue priority1;
    priority1.first = priority1.last = new Qnode{"alpha", nullptr};

    // Create the PQ
    PQ pq = new PQnode{1, priority1, nullptr};

    // Test PQ_leave
    PQ_leave(pq);
    EXPECT_TRUE(PQ_isEmpty(pq));

    // Clean up
    delete pq;
}

TEST(leaveNew, givenTwoElementPQWithUniquePriorityExpectLeaveRemovesFirstPQNode)
{
    // Create the two Queues for the PQ
    Queue priority1;
    priority1.first = priority1.last = new Qnode{"alpha", nullptr};
    Queue priority2;
    priority2.first = priority2.last = new Qnode{"beta", nullptr};

    // Create the PQ
    PQ pq = new PQnode{1, priority1, new PQnode{2, priority2, nullptr}};

    // Test PQ_leave
    PQ_leave(pq);
    EXPECT_EQ("beta", PQ_first(pq));

    // Clean up
    delete pq;
    delete priority2.first;
}

TEST(sizeByPriorityNew, givenNonExistantPriorityExpectSizeByPriorityIsZero)
{
    // Create the two Queues for the PQ
    Queue priority1;
    priority1.first = new Qnode{"alpha", new Qnode{"beta", nullptr}};
    priority1.last = priority1.first->next;
    Queue priority2;
    priority2.first = priority2.last = new Qnode{"delta", nullptr};

    // Create the PQ
    PQ pq = new PQnode{1, priority1, new PQnode{3, priority2, nullptr}};

    // Test PQ_sizeByPriority
    EXPECT_EQ(PQ_sizeByPriority(pq, 2), 0);

    // Clean up
    delete pq->next;
    delete pq;
    delete priority1.first;
    delete priority1.last;
    delete priority2.first;
}

TEST(sizeByPriorityNew, givenPriorityTooLargeExpectSizeByPriorityIsZero)
{
    // Create the two Queues for the PQ
    Queue priority1;
    priority1.first = new Qnode{"alpha", new Qnode{"beta", nullptr}};
    priority1.last = priority1.first->next;
    Queue priority2;
    priority2.first = priority2.last = new Qnode{"delta", nullptr};

    // Create the PQ
    PQ pq = new PQnode{1, priority1, new PQnode{2, priority2, nullptr}};

    // Test PQ_sizeByPriority
    EXPECT_EQ(PQ_sizeByPriority(pq, 3), 0);

    // Clean up
    delete pq->next;
    delete pq;
    delete priority1.first;
    delete priority1.last;
    delete priority2.first;
}

TEST(sizeByPriorityNew, givenInvalidPriorityExpectSizeByPriorityIsZero)
{
    // Create the two Queues for the PQ
    Queue priority1;
    priority1.first = new Qnode{"alpha", new Qnode{"beta", nullptr}};
    priority1.last = priority1.first->next;
    Queue priority2;
    priority2.first = priority2.last = new Qnode{"delta", nullptr};

    // Create the PQ
    PQ pq = new PQnode{1, priority1, new PQnode{2, priority2, nullptr}};

    // Test PQ_sizeByPriority
    EXPECT_EQ(PQ_sizeByPriority(pq, -17), 0);

    // Clean up
    delete pq->next;
    delete pq;
    delete priority1.first;
    delete priority1.last;
    delete priority2.first;
}

TEST(numPrioritiesNew, givenOnePQNodeExpectOnePriority)
{
    // Create a Queue for the PQ
    Queue priority1;
    priority1.first = new Qnode{"alpha", new Qnode{"beta", nullptr}};
    priority1.last = priority1.first->next;

    // Create the PQ
    PQ pq = new PQnode{1, priority1, nullptr};

    // Test PQ_numPriorities
    EXPECT_EQ(PQ_numPriorities(pq), 1);

    // Clean up
    delete pq;
    delete priority1.first;
    delete priority1.last;
}

TEST(numPrioritiesNew, givenTwoPQNodesExpectTwoPriorities)
{
    // Create the two Queues for the PQ
    Queue priority1;
    priority1.first = new Qnode{"alpha", new Qnode{"beta", nullptr}};
    priority1.last = priority1.first->next;
    Queue priority2;
    priority2.first = priority2.last = new Qnode{"delta", nullptr};

    // Create the PQ
    PQ pq = new PQnode{1, priority1, new PQnode{2, priority2, nullptr}};

    // Test PQ_numPriorities
    EXPECT_EQ(PQ_numPriorities(pq), 2);

    // Clean up
    delete pq->next;
    delete pq;
    delete priority1.first;
    delete priority1.last;
    delete priority2.first;
}

/* ************************************************************** */
/* DO NOT SUBMIT                                                  */
/* ************************************************************** */

TEST(gcovMakeup, testQueueNuke)
{
    Queue q;
    Q_init(q);
    Q_enter(q, "test");
    Q_nuke(q);
}