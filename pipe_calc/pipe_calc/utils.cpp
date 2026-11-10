#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>

#include "utils.h"

using namespace std;

// replay of a log: while it goes, cin reads the inputs from replay_stream instead of the keyboard
static istringstream replay_stream;
static streambuf* console_buf = nullptr;
static bool replaying = false;

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

// writes the input to the log, during a replay also shows it (nobody types it)
void log_input(string text)
{
    if (replaying)
        cout << text << "\n";
    log_action("Input: " + text);
}

// replay

void check_replay_end()
{
    if (replaying && (cin >> ws).eof())
    {
        cin.clear();
        cin.rdbuf(console_buf);
        replaying = false;
        cout << "\nReplay finished, you can continue manually.\n";
        log_action("Replay finished");
    }
}

bool start_replay(string name_file)
{
    ifstream file(name_file);
    if (!file)
    {
        log_error("Replay of " + name_file + " failed: file not found.");
        return false;
    }
    vector<string> inputs;
    string line;
    bool skip = false;
    while (getline(file, line))
    {
        if (line.length() < 20)
            continue;
        string text = line.substr(20);

        if (text.substr(0, 7) == "Input: ")
        {
            if (!skip && text.length() > 7)
                inputs.push_back(text.substr(7));
        }
        else if (text == "Menu item 10")
        {
            if (!inputs.empty())
                inputs.pop_back();
            skip = true;
        }
        else if (text.find("Replay of ") != string::npos)
        {
            skip = false;
        }
        else if (text == "Menu item 0")
        {
            if (!inputs.empty())
                inputs.pop_back();
            break;
        }
    }

    if (inputs.empty())
    {
        log_error("Replay of " + name_file + " failed: no actions in the file.");
        return false;
    }

    string all_inputs;
    for (string input : inputs)
        all_inputs += input + "\n";
    replay_stream.clear();
    replay_stream.str(all_inputs);
    console_buf = cin.rdbuf(replay_stream.rdbuf());
    replaying = true;
    cout << "Replay of " << name_file << " started.\n";
    log_action("Replay of " + name_file + " started");
    return true;
}

// functions for check input

int int_input(string message, int min_value, int max_value)
{
    int input;
    string rest;
    while (true)
    {
        check_replay_end();
        cout << message;
        cin >> input;
        if (cin.fail() || cin.peek() != '\n')
        {
            string wrong;
            if (!cin.fail()) wrong = to_string(input);
            cin.clear();
            getline(cin, rest);
            log_input(wrong + rest);
            log_error("The value entered was not a integer number. Enter a valid value.");
        }
        else if (input < min_value || input > max_value)
        {
            log_input(to_string(input));
            log_error("The value must be from " + to_string(min_value) + " to " + to_string(max_value) + ".");
        }
        else
        {
            log_input(to_string(input));
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
        check_replay_end();
        cout << message;
        cin >> input;
        if (cin.fail() || cin.peek() != '\n')
        {
            string wrong;
            if (!cin.fail()) wrong = to_string(input);
            cin.clear();
            getline(cin, rest);
            log_input(wrong + rest);
            log_error("The value entered was not a number. Enter a valid value.");
        }
        else if (input <= 0)
        {
            log_input(to_string(input));
            log_error("The value must be positive. Enter a valid value.");
        }
        else
        {
            log_input(to_string(input));
            return input;
        }
    }
}

bool bool_input(string message)
{
    string input;
    while (true)
    {
        check_replay_end();
        cout << message << " (y/n): ";
        getline(cin >> ws, input);
        log_input(input);
        if (input == "y") return true;
        if (input == "n") return false;
        log_error("Enter y or n");
    }
}

string string_input(string message)
{
    string input;
    check_replay_end();
    cout << message;
    getline(cin >> ws, input);
    log_input(input);
    return input;
}

// helpers

vector<int> sorted_ids(const unordered_set<int>& ids)
{
    vector<int> result(ids.begin(), ids.end());
    sort(result.begin(), result.end());
    return result;
}

string ids_to_string(const unordered_set<int>& ids)
{
    string result;
    for (int id : sorted_ids(ids))
        result += to_string(id) + " ";
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
            log_error("This ID is not among the found objects.");
        else if (chosen.count(id) != 0) 
            log_error("This ID is already chosen.");
        else chosen.insert(id);
    }
    if (chosen.empty())
    {
        log_error("Nothing chosen.");
    }
    return chosen;
}
