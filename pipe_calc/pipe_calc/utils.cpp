#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

#include "utils.h"

using namespace std;

// log

void log_action(string text)
{
    time_t now = time(0);
    tm t;
    localtime_s(&t, &now);
    static string name_file = "";
    if (name_file == "")
    {
        char name[28];
        strftime(name, sizeof(name), "log_%Y-%m-%d_%H-%M-%S.txt", &t);
        name_file = name;
    }

    ofstream file(name_file, ios::app);
    char date[20];
    strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", &t);
    file << date << " " << text << "\n";
}

// shows the error and writes it to the log
void log_error(string text)
{
    cout << text << "\n";
    log_action("Error: " + text);
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
            log_action("Input: " + wrong + rest);
            log_error("The value entered was not a integer number. Enter a valid value.");
        }
        else if (input < min_value || input > max_value)
        {
            log_action("Input: " + to_string(input));
            log_error("The value must be from " + to_string(min_value) + " to " + to_string(max_value) + ".");
        }
        else
        {
            log_action("Input: " + to_string(input));
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
            log_action("Input: " + wrong + rest);
            log_error("The value entered was not a number. Enter a valid value.");
        }
        else if (input <= 0)
        {
            log_action("Input: " + to_string(input));
            log_error("The value must be positive. Enter a valid value.");
        }
        else
        {
            log_action("Input: " + to_string(input));
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
        log_action("Input: " + input);
        if (input == "y") return true;
        if (input == "n") return false;
        log_error("Enter y or n");
    }
}

string string_input(string message)
{
    string input;
    cout << message;
    getline(cin >> ws, input);
    log_action("Input: " + input);
    return input;
}

string filename_input(string message)
{
    string input;
    while (true)
    {
        input = string_input(message);
        if (input.length() < 3)
        {
            log_error("File name is too short, must be like name.txt");
        }
        else
        {
            return input;
        }
    }
}

// helpers

string ids_to_string(const set<int>& ids)
{
    string result;
    for (int id : ids) result += to_string(id) + " ";
    return result;
}

set<int> choose_ids(const set<int>& found)
{
    set<int> chosen;
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
        if (id == 0) break;
        if (found.count(id) == 0) log_error("This ID is not among the found objects.");
        else if (chosen.count(id) != 0) log_error("This ID is already chosen.");
        else chosen.insert(id);
    }
    if (chosen.empty())
    {
        log_error("Nothing chosen.");
    }
    return chosen;
}
