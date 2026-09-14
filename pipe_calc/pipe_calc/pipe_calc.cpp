#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

struct Pipe
{
    string name_p;
    int diam;
    double length;
    bool in_repair;
};

struct CS
{
    string name_cs;
    int amount_ws;
    int amount_ws_in_progress;
    string class_cs;
};

bool pipe_exist = false;
bool cs_exist = false;
Pipe pipe;
CS cs;

// functions for check input

int int_input(string message)
{
    int input;
    while (true)
    {
        cout << message;
        cin >> input;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1111, '\n');
            cout << "The value entered was not a integer number. Enter a valid value.\n";
        }
        else
        {
            cin.ignore(1111, '\n');
            return input;
        }
    }
}

double double_input(string message)
{
    double input;
    while (true)
    {
        cout << message;
        cin >> input;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1111, '\n');
            cout << "The value entered was not a number. Enter a valid value.\n";
        }
        else
        {
            cin.ignore(1111, '\n');
            return input;
        }
    }
}

bool bool_input(string message) 

{
    string input;
    while (true)
    {
        cout << message << "(y/n)";
        getline(cin, input);
        if (input == "y") return true;
        if (input == "n") return false;
        cout << "Enter y or n";
    }
}

string string_input(string message)
{
    string input;
    while (true)
    {
        cout << message;
        getline(cin, input);
        if (input == "")
        {
            cout << "Cannot be empty. Enter something.";
        }
        else
        {
            return input;
        }
    }
}

// menu

void menu()
{
    cout << " 1. Add pipe\n";
    cout << " 2. Add cs\n";
    cout << " 3. View all objects\n";
    cout << " 4. Edit pipe\n";
    cout << " 5. Edit compressor station\n";
    cout << " 6. Save\n";
    cout << " 7. Load\n";
    cout << " 0. Exit\n";
}

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
}