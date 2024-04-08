/*
 * CS138, W23, Assignment 2, Problem 1
 * Main Function
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

vector<string> text_justify(vector<string> lines, int n);
string line_justify(string line, int n);
string sentence_justify(string line, int n);

vector<string> text_r_right(vector<string> lines, int n);
vector<string> text_r_left(vector<string> lines, int n);
vector<string> text_center(vector<string> lines, int n);

vector<string> generate_lines(vector<string> strs, int n);
void print_vector(vector<string> lines, bool reverse, string filter);

int main()
{
    int n;
    cin >> n;
    if (n < 0)
    {
        cerr << "Error, line length must be positive." << endl;
        return 1;
    }

    // Openning file
    string fileName;
    cin >> fileName;
    ifstream input_stream{fileName};
    if (!input_stream)
    {
        cerr << "Error, cannot open specified text file." << endl;
        return 1;
    }

    // Reading from file
    vector<string> raw_input;
    string x;
    while (input_stream >> x)
    {
        raw_input.push_back(x.substr(0, n));
    }

    vector<string> lines = generate_lines(raw_input, n);
    vector<string> output_lines = lines;
    bool reverse_flag = false;

    string command;
    while (cin >> command)
    {
        if (command == "rr")
        {
            output_lines = text_r_right(lines, n);
        }
        else if (command == "rl")
        {
            output_lines = text_r_left(lines, n);
        }
        else if (command == "c")
        {
            output_lines = text_center(lines, n);
        }
        else if (command == "j")
        {
            output_lines = text_justify(lines, n);
        }
        else if (command == "f")
        {
            reverse_flag = false;
        }
        else if (command == "r")
        {
            reverse_flag = true;
        }
        else if (command == "p")
        {
            print_vector(output_lines, reverse_flag, "");
        }
        else if (command == "k")
        {
            int index;
            cin >> index;
            cout << output_lines.at(index) << endl;
        }
        else if (command == "s")
        {
            string filter;
            cin >> filter;
            print_vector(output_lines, reverse_flag, filter);
        }
        else if (command == "q")
        {
            break;
        }
        else
        {
            cerr << "Error, command is illegal." << endl;
            return 1;
        }
    }

    return 0;
}

vector<string> generate_lines(vector<string> strs, int n)
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

            lines.push_back(curr_line);
            curr_line = token;
        }
        else
        {
            curr_line += " " + token;
        }
    }
    lines.push_back(curr_line);
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

void print_vector(vector<string> lines, bool reverse, string filter)
{
    if (reverse)
    {
        for (int i = lines.size() - 1; i >= 0; i--)
        {
            if (lines.at(i).find(filter) != string::npos)
            {
                cout << lines.at(i) << endl;
            }
        }
    }
    else
    {
        for (string line : lines)
        {
            if (line.find(filter) != string::npos)
            {
                cout << line << endl;
            }
        }
    }
}