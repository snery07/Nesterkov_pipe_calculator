#include <Windows.h>
#include <iostream>
#include <string>
#include <fstream>

#include "utils.h"

using namespace std;

// log: everything the user enters, one input per line
//source: https://gist.github.com/JustVugg/46aabef46cbd50191da5c9ef6e703317

string log_path()
{
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    string exe_path = path;
    return exe_path.substr(0, exe_path.find_last_of('\\') + 1) + "log.txt";
}

void writelog(const string& text)
{
    ofstream file(log_path(), ios::app);
    if (file) file << text << "\n";
}

// functions for check input

int int_input(string message, int min_value, int max_value)
{
    int input;
    string rest;
    while (true)
    {
        cout << message;
        cin >> input;
        if (cin.fail() || cin.peek() != '\n')
        {
            string wrong;
            if (!cin.fail()) wrong = to_string(input);
            cin.clear();
            getline(cin, rest);
            writelog(wrong + rest);
            cout << "The value entered was not a integer number. Enter a valid value.\n";
        }
        else if (input < min_value || input > max_value)
        {
            writelog(to_string(input));
            cout << "The value must be from " << min_value << " to " << max_value << ".\n";
        }
        else
        {
            writelog(to_string(input));
            return input;
        }
    }
}

double double_input(string message)
{
    double input;
    string rest;
    while (true)
    {
        cout << message;
        cin >> input;
        if (cin.fail() || cin.peek() != '\n')
        {
            string wrong;
            if (!cin.fail()) wrong = to_string(input);
            cin.clear();
            getline(cin, rest);
            writelog(wrong + rest);
            cout << "The value entered was not a number. Enter a valid value.\n";
        }
        else if (input <= 0)
        {
            writelog(to_string(input));
            cout << "The value must be positive. Enter a valid value.\n";
        }
        else
        {
            writelog(to_string(input));
            return input;
        }
    }
}

bool bool_input(string message)
{
    string input;
    while (true)
    {
        cout << message << " (y/n): ";
        getline(cin >> ws, input);
        writelog(input);
        if (input == "y") return true;
        if (input == "n") return false;
        cout << "Enter y or n\n";
    }
}

string string_input(string message)
{
    string input;
    cout << message;
    getline(cin >> ws, input);
    writelog(input);
    return input;
}

// helpers

vector<int> sorted_ids(const unordered_set<int>& ids)
{
    vector<int> result(ids.begin(), ids.end());
    sort(result.begin(), result.end());
    return result;
}

unordered_set<int> choose_ids(const unordered_set<int>& found)
{
    unordered_set<int> chosen;
    int option;
    cout << "1. All found\n";
    cout << "2. Choose by ID\n";
    cout << "0. Cancel\n";
    option = int_input("Select one of the menu items: ", 0, 2);
    if (option == 0) return chosen;
    if (option == 1) return found;

    int id;
    while (true)
    {
        id = int_input("Enter ID (0 to finish): ");
        if (id == 0)
            break;
        if (found.count(id) == 0)
            cout << "This ID is not among the found objects.\n";
        else if (chosen.count(id) != 0)
            cout << "This ID is already chosen.\n";
        else chosen.emplace(id);
    }
    if (chosen.empty())
    {
        cout << "Nothing chosen.\n";
    }
    return chosen;
}
