/*
 * CS138, W23, Assignment 1, Problem 4
 * Main Function
 *
 * main function is a special function,
 * which serves as the entry point for the program.
 *
 * Try to keep it as simple as possible
 * and implement the logic of your program
 * in a1q4.cpp, so that you can write unit tests
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

    vector<string> lines;
    string curr_line = "";
    for (string token : v)
    {
        if (curr_line.size() == 0)
        {
            curr_line += token;
        }
        else if (curr_line.size() + 1 + token.size() > N)
        {
            lines.push_back(curr_line);
            curr_line = token;
        }
        else
        {
            curr_line += " " + token;
        }
    }
    lines.push_back(curr_line);

    for (string line : lines)
    {
        if (line.size() == N)
        {
            cout << line << endl;
            continue;
        }
        if (line.find(" ") == string::npos)
        {
            while (line.size() != N)
            {
                line += " ";
            }
            cout << line << endl;
            continue;
        }
        while (line.size() != N)
        {
            bool ws_flag = false;
            for (int i = 0; i < line.size(); i++)
            {
                if (ws_flag)
                {
                    if (line.at(i) != ' ')
                    {
                        ws_flag = false;
                        line.insert(i, 1, ' ');
                        if (line.size() == N)
                        {
                            break;
                        }
                    }
                }
                else
                {
                    if (line.at(i) == ' ')
                    {
                        ws_flag = true;
                    }
                }
            }
        }
        cout << line << endl;
    }
    return 0;
}