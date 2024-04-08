/*
 * CS138, W23, Assignment 1, Problem 3
 * Main Function
 *
 * main function is a special function,
 * which serves as the entry point for the program.
 *
 * Try to keep it as simple as possible
 * and implement the logic of your program
 * in a1q3.cpp, so that you can write unit tests
 * for them and make sure of their expected behavior.
 */
#include <iostream>
#include <vector>
#include <string>
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
    string x;
    while (cin >> x)
    {
        v.push_back(x.substr(0, N));
    }

    int count = 0;
    for (string token : v)
    {
        if (count == 0)
        {
            cout << token;
            count += token.size();
        }
        else if (count + 1 + token.size() > N)
        {
            cout << endl
                 << token;
            count = token.size();
        }
        else
        {
            cout << " " << token;
            count += token.size() + 1;
        }
    }
    cout << endl;
    return 0;
}