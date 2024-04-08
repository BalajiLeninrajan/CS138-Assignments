#include <iostream>
#include <string>
#include <cassert>
#include "a4p1.h"

using namespace std;

// Provided implementations of Queue routines using linked list.

void Q_init(Queue &q)
{
    q.first = nullptr;
    q.last = nullptr;
}

bool Q_isEmpty(const Queue &q)
{
    return nullptr == q.first;
}

void Q_enter(Queue &q, string val)
{
    Qnode *p = new Qnode{};
    p->val = val;
    p->next = nullptr;
    if (Q_isEmpty(q))
    {
        q.first = p;
    }
    else
    {
        q.last->next = p;
    }
    q.last = p;
}

string Q_first(const Queue &q)
{
    assert(!Q_isEmpty(q));
    return q.first->val;
}

void Q_leave(Queue &q)
{
    assert(!Q_isEmpty(q));
    Qnode *p = q.first;
    q.first = q.first->next;
    if (nullptr == q.first)
    {
        q.last = nullptr;
    }
    delete p;
}

void Q_nuke(Queue &q)
{
    while (!Q_isEmpty(q))
    {
        Q_leave(q);
    }
}

// New function
int Q_size(Queue &q)
{
    int count = 0;
    for (Qnode *curr = q.first; curr; curr = curr->next)
    {
        count++;
    }
    return count;
}

// Implement the following PQ routines, making use of the given Queue routines.

// Free sample :)
void PQ_init(PQ &pq)
{
    pq = nullptr;
}

bool PQ_isEmpty(const PQ &pq)
{
    return pq == nullptr;
}

void PQ_enter(PQ &pq, std::string val, int priority)
{
    PQnode *curr = pq;

    // For appending at start
    if (PQ_isEmpty(pq) || curr->priority > priority)
    {
        Queue newQueue;
        Q_init(newQueue);
        Q_enter(newQueue, val);
        pq = new PQnode{priority, newQueue, curr};
        return;
    }
    else if (curr->priority == priority)
    {
        Q_enter(curr->q, val);
        return;
    }

    // Traverse Queue
    while (curr->next)
    {
        if (curr->next->priority == priority)
        {
            Q_enter(curr->next->q, val);
            return;
        }
        else if (curr->next->priority > priority)
        {
            break;
        }
        curr = curr->next;
    }

    // Add new node to middle/end
    Queue newQueue;
    Q_init(newQueue);
    Q_enter(newQueue, val);
    curr->next = new PQnode{priority, newQueue, curr->next};
}

std::string PQ_first(const PQ &pq)
{
    if (PQ_isEmpty(pq))
    {
        cerr << "Error, priority queue is empty." << endl;
        exit(1);
    }
    return Q_first(pq->q);
}
void PQ_leave(PQ &pq)
{
    if (PQ_isEmpty(pq))
    {
        cerr << "Error, priority queue is empty." << endl;
        exit(1);
    }
    Q_leave(pq->q);
    if (Q_isEmpty(pq->q))
    {
        PQnode *tmp = pq;
        pq = pq->next;
        delete tmp;
    }
}

int PQ_size(const PQ &pq)
{
    int count = 0;
    if (PQ_isEmpty(pq))
    {
        return count;
    }
    for (PQnode *curr = pq; curr; curr = curr->next)
    {
        count += Q_size(curr->q);
    }
    return count;
}

int PQ_sizeByPriority(const PQ &pq, int priority)
{
    for (PQnode *curr = pq; curr; curr = curr->next)
    {
        if (curr->priority == priority)
        {
            return Q_size(curr->q);
        }
        else if (curr->priority > priority)
        {
            break;
        }
    }
    return 0;
}

int PQ_numPriorities(const PQ &pq)
{
    int count = 0;
    for (PQnode *curr = pq; curr; curr = curr->next)
    {
        count++;
    }
    return count;
}

void PQ_nuke(PQ &pq)
{
    while (!PQ_isEmpty(pq))
    {
        PQ_leave(pq);
    }
}