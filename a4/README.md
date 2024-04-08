# CS138 W24 Assignment 4 README

This assignment has three different parts, as described in the PDF.
Each part will have you implement various functions for interfacing
with a different data structure.

1. Part 1 involves working with the List-Of-Lists (LOL) implementation of priority queues.
2. Part 2 involves working with binary search trees.
3. Part 3 involves working with queues and binary search trees.

Each part has two submissions to Marmoset:

- Tests
- Code

For a total of 6 Marmoset submissions:

1. Tests for Part 1 - a4p1t
2. Tests for Part 2 - a4p2t
3. Tests for Part 3 - a4p3t
3. Code for Part 1 - a4p1c
4. Code for Part 2 - a4p2c
4. Code for Part 3 - a4p3c

To submit parts to Marmoset individually, you can use the
`submit_project.sh` script. This will look like:

- `./submit_project.sh 1t`
- `./submit_project.sh 2t`
- `./submit_project.sh 3t`
- `./submit_project.sh 1c`
- `./submit_project.sh 2c`
- `./submit_project.sh 3c`

Alternatively, there is a script that does all 6 submissions for you:

    `submit_all.sh`


## Test case coverage is measured on staff code

Just like in assignment 2 and 3, the test cases you create for this assignment
will be assessed by measuring their coverage _of the staff code_. The provided test
files contains exact copies of all the Marmoset public tests for the corresponding
part. The coverage threshold for each part is written at the top of the test files.

## 

## Provided Scripts:
Replace <part_num> with 1, 2, or 3 depending on which part of the assignment you
are working on.

`run_gtest.sh <part_num>`

This script compiles your a4pX.cc file, then tests it against the Google Test suites.

`run_gcov.sh <part_num>`

This script compiles your a4pX.cc, then tests it against the Google Test suites, then reports
your gcov coverage.

`run_valgrind.sh <part_num>`

This script compiles your a4pX.cc file, then tests it against the Google Test suites with
Valgrind. Note that Valgrind errors can be cause by issues in both a4pX.cc and a4pXTest.cc.
