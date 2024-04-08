/*
 * CS138, W23, Assignment 1, Problem 1
 * Main Function
 *
 * main function is a special function,
 * which serves as the entry point for the program.
 *
 * Try to keep it as simple as possible
 * and implement the logic of your program
 * in a1q1.cpp, so that you can write unit tests
 * for them and make sure of their expected behavior.
 */
#include <iostream>
#include <vector>
using namespace std;

// no argc+argv because we aren't using them in A1
int main()
{
    int N;
    cin >> N;
    if (N < 0)
    {
        cerr << "Error, line length must be positive." << endl;
        return 1;
    }

    vector<string> v;
    cin.ignore();
    while (true)
    {
        string x;
        getline(cin, x);
        if (!cin)
        {
            break;
        }

        v.push_back(x.substr(0, N));
    }

    for (string i : v)
    {
        cout << i << endl;
    }

    return 0;
}
