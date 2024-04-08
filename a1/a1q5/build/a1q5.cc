/*
 * CS138, W23, Assignment 1, Problem 5
 * Main Function
 *
 * main function is a special function,
 * which serves as the entry point for the program.
 *
 * Try to keep it as simple as possible
 * and implement the logic of your program
 * in a1q5.cpp, so that you can write unit tests
 * for them and make sure of their expected behavior.
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<string> get_usr_strs(int n);
vector<string> generate_lines(vector<string> strs, int n, bool flag);

vector<string> text_justify(vector<string> lines, int n);
string line_justify(string line, int n);
string sentence_justify(string line, int n);

vector<string> text_r_right(vector<string> lines, int n);
vector<string> text_r_left(vector<string> lines, int n);
vector<string> text_center(vector<string> lines, int n);

void print_vector(vector<string> lines, bool flag);

// no argc+argv because we aren't using them in A1
int main()
{
    int N;
    string c1;
    char c2;
    cin >> N >> c1 >> c2;
    if (N < 0)
    {
        cerr << "Error, line length must be positive." << endl;
        return 1;
    }

    bool filter_fnord = false;
    bool reverse_flag = false;

    if (c1 != "rr" && c1 != "j" && c1 != "rl" && c1 != "c")
    {
        cerr << "Error, command is illegal." << endl;
        return 1;
    }

    if (c2 == 'g')
    {
        filter_fnord = true;
    }
    else if (c2 == 'r')
    {
        reverse_flag = true;
    }
    else if (c2 != 'f')
    {
        cerr << "Error, command is illegal." << endl;
        return 1;
    }

    vector<string> v = get_usr_strs(N);
    vector<string> lines = generate_lines(v, N, filter_fnord);

    if (c1 == "rr")
    {
        lines = text_r_right(lines, N);
    }
    else if (c1 == "j")
    {
        lines = text_justify(lines, N);
    }
    else if (c1 == "rl")
    {
        lines = text_r_left(lines, N);
    }
    else
    {
        lines = text_center(lines, N);
    }

    print_vector(lines, reverse_flag);
    return 0;
}

vector<string> get_usr_strs(int n)
{
    vector<string> v;
    cin.ignore();
    string x;
    while (cin >> x)
    {
        v.push_back(x.substr(0, n));
    }
    return v;
}

vector<string> generate_lines(vector<string> strs, int n, bool flag)
{
    vector<string> lines;
    string curr_line = "";
    for (string token : strs)
    {
        if (curr_line.size() == 0)
        {
            curr_line += token;
        }
        else if (curr_line.size() + 1 + token.size() > n)
        {
            if (!flag || curr_line.find("fnord") != string::npos)
            {
                lines.push_back(curr_line);
            }
            curr_line = token;
        }
        else
        {
            curr_line += " " + token;
        }
    }
    if (!flag || curr_line.find("fnord") != string::npos)
    {
        lines.push_back(curr_line);
    }
    return lines;
}

vector<string> text_r_right(vector<string> lines, int n)
{
    vector<string> res;
    for (string line : lines)
    {
        while (line.size() != n)
        {
            line += " ";
        }
        res.push_back(line);
    }
    return res;
}

vector<string> text_justify(vector<string> lines, int n)
{
    vector<string> res;
    for (string line : lines)
    {
        res.push_back(line_justify(line, n));
    }
    return res;
}

string line_justify(string line, int n)
{
    if (line.size() == n)
    {
        return line;
    }
    if (line.find(" ") == string::npos)
    {
        while (line.size() != n)
        {
            line += " ";
        }
        return line;
    }

    return sentence_justify(line, n);
}

string sentence_justify(string line, int n)
{
    while (true)
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
                    if (line.size() == n)
                    {
                        return line;
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
}

vector<string> text_r_left(vector<string> lines, int n)
{
    vector<string> res;
    for (string line : lines)
    {
        while (line.size() != n)
        {
            line = " " + line;
        }
        res.push_back(line);
    }
    return res;
}

vector<string> text_center(vector<string> lines, int n)
{
    vector<string> res;
    for (string line : lines)
    {
        bool fb_flag = true;
        while (line.size() != n)
        {
            if (fb_flag)
            {
                line = " " + line;
                fb_flag = !fb_flag;
            }
            else
            {
                line += " ";
                fb_flag = !fb_flag;
            }
        }
        res.push_back(line);
    }
    return res;
}

void print_vector(vector<string> lines, bool flag)
{
    if (flag)
    {
        for (int i = lines.size() - 1; i >= 0; i--)
        {
            cout << lines.at(i) << endl;
        }
    }
    else
    {
        for (string line : lines)
        {
            cout << line << endl;
        }
    }
}