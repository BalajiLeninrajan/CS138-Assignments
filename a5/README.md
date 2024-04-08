# CS138 W24 Assignment 5 README

This assignment has two different parts, as described in the PDF.
Each part will have you implement various methods for different classes.

1. Part 1 involves implementing an abstract base class and its derived classes.
2. Part 2 involves working with a class with a tree structure.

Each part has two submissions to Marmoset:

- Tests
- Code

For a total of 4 Marmoset submissions:

1. Tests for Part 1 - a5p1t
2. Tests for Part 2 - a5p2t
3. Code for Part 1 - a5p1c
4. Code for Part 2 - a5p2c

To submit parts to Marmoset individually, you can use the
`submit_project.sh` script. This will look like:

- `./submit_project.sh 1t`
- `./submit_project.sh 2t`
- `./submit_project.sh 1c`
- `./submit_project.sh 2c`

## Test case coverage is measured on staff code

Just like in previous assignments, the test cases you create for this assignment
will be assessed by measuring their coverage _of the staff code_. The provided test
files contain exact copies of all the Marmoset public tests for the corresponding
part. The coverage threshold for each part is written at the top of the test files.

## Provided Scripts:
Replace <part_num> with 1 or 2 depending on which part of the assignment you
are working on.

`run_gtest.sh <part_num>`

This script compiles your a5pX.cc file, then tests it against the Google Test suites.

`run_gcov.sh <part_num>`

This script compiles your a5pX.cc, then tests it against the Google Test suites, then reports
your gcov coverage.

`run_valgrind.sh <part_num>`

This script compiles your a5pX.cc file, then tests it against the Google Test suites with
Valgrind. Note that Valgrind errors can be caused by issues in both a5pX.cc and a5pXTest.cc.
