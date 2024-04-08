/*
 * CS138, W23, Assignment 1, Problem 2
 * Main Function
 *
 * main function is a special function,
 * which serves as the entry point for the program.
 *
 * Try to keep it as simple as possible
 * and implement the logic of your program
 * in a1q2.cpp, so that you can write unit tests
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
    char command;
    cin >> N >> command;
    if (N < 0)
    {
        cerr << "Error, line length must be positive." << endl;
        return 1;
    }

    bool filter_fnord = false;
    bool reverse_flag = false;

    if (command == 'g')
    {
        filter_fnord = true;
    }
    else if (command == 'r')
    {
        reverse_flag = true;
    }
    else if (command != 'f')
    {
        cerr << "Error, command is illegal." << endl;
        return 1;
    }

    cin.ignore();
    vector<string> v;
    while (true)
    {
        string x;
        getline(cin, x);
        if (!cin)
        {
            break;
        }

        if (!filter_fnord)
        {
            v.push_back(x.substr(0, N));
        }
        else if (x.find("fnord") != string::npos)
        {
            v.push_back(x.substr(0, N));
        }
    }

    if (reverse_flag)
    {
        for (int i = v.size() - 1; i >= 0; i--)
        {
            cout << v.at(i) << endl;
        }
    }
    else
    {
        for (string i : v)
        {
            cout << i << endl;
        }
    }

    return 0;
}
