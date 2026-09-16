#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>

using namespace std;

struct Pipe
{
    string name_pipe;
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
        else if (input < 0)
        {
            cin.ignore(1111, '\n');
            cout << "The value must be positive. Enter a valid value.\n";
        }
        else
        {
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
        else if (input <= 0)
        {
            cin.ignore(1111, '\n');
            cout << "The value must be positive. Enter a valid value.\n";
        }
        else
        {
            return input;
        }
    }
}

bool bool_input(string message)
{
    string input;
    while (true)
    {
        cout << message << "(y/n) ";
        getline(cin >> ws, input);
        if (input == "y") return true;
        if (input == "n") return false;
        cout << "Enter y or n\n";
    }
}

string string_input(string message)
{
    string input;
    while (true)
    {
        cout << message;
        getline(cin >> ws, input);
        if (input == "")
        {
            cout << "Cannot be empty. Enter something.\n";
        }
        else
        {
            return input;
        }
    }
}

string filename_input(string message)
{
    string input;
    while (true)
    {
        cout << message;
        getline(cin >> ws, input);
        if (input == "")
        {
            cout << "Cannot be empty. Enter something.\n";
        }
        else if (input.length() < 3)
        {
            cout << "File name is too short, must be like name.txt\n";
        }
        else
        {
            return input;
        }
    }
}

// addition functions

void add_cs(CS& cs, bool& cs_exist)
{
    cout << "\nEnter the data for the compressor station:\n";
    cs.name_cs = string_input("Name: ");
    cs.amount_ws = int_input("Amount of workshops: ");
    cs.amount_ws_in_progress = int_input("Amount of workshops in progress: ");
    while (cs.amount_ws_in_progress > cs.amount_ws)
    {
        cout << "Amount of workshops in progress cannot be greater then amount of workshops\n";
        cs.amount_ws_in_progress = int_input("Amount of workshops in progress: ");
    }
    cs.class_cs = string_input("Class of compressor station: ");
    cs_exist = true;
    cout << "Compressor station added!\n";
}

void add_pipe(Pipe& pipe, bool& pipe_exist)
{
    cout << "\nEnter the data for the pipe:\n";
    pipe.name_pipe = string_input("Kilometer mark (name): ");
    pipe.length = double_input("Length (km): ");
    pipe.diam = int_input("Diameter (mm): ");
    pipe.in_repair = bool_input("Under repair status: ");
    pipe_exist = true;
    cout << "Pipe added!\n";
}

// editing functions

void edit_cs(CS& cs, bool cs_exist)
{
    if (cs_exist == false)
    {
        cout << "The compressor station was not added yet. Add it first.\n";
        return;
    }
    int option;
    cout << "The workshops is currently in progress: " << cs.amount_ws_in_progress << "/" << cs.amount_ws << "\n";
    cout << "1. Start worksop\n";
    cout << "2. Stop workshop\n";
    cout << "0. Exit\n";
    option = int_input("Select one of the menu items: ");
    int amount_ws;
    if (option == 1)
    {
        if (cs.amount_ws_in_progress == cs.amount_ws)
        {
            cout << "All worksops already in progress!";
        }
        else
        {
            amount_ws = int_input("Enter amount of workshops you want to start: ");
            if (amount_ws > (cs.amount_ws - cs.amount_ws_in_progress))
            {
                cout << "Amount of workshops you want to start cannot be greater than amount of available workshops!\n";
            }
            else
            {
                cs.amount_ws_in_progress += amount_ws;
                cout << "The workshops started. Currently in progress: " << cs.amount_ws_in_progress << "/" << cs.amount_ws << "\n";
            }
        }
    }
    else if (option == 2)
    {
        if (cs.amount_ws_in_progress == 0)
        {
            cout << "Not a single workshop had been launched yet!\n";
        }
        else
        {
            amount_ws = int_input("Enter amount of workshops you want to stop: ");
            if (amount_ws > cs.amount_ws_in_progress)
            {
                cout << "Amount of workshops you want to stop cannot be greater than amount of workshops currently in progress!\n";
            }
            else
            {
                cs.amount_ws_in_progress -= amount_ws;
                cout << "The workshops stopped. Currently in progress: " << cs.amount_ws_in_progress << "/" << cs.amount_ws << "\n";
            }
        }
    }
    else if (option == 0)
    {
        return;
    }
    else
    {
        cout << "Wrong menu item.\n";
    }
}

void edit_pipe(Pipe& pipe, bool pipe_exist)
{
    if (pipe_exist == false)
    {
        cout << "The pipe was not added yet. Add it first.\n";
        return;
    }
    int option;
    cout << "1. Edit under repair status\n";
    cout << "0. Exit\n";
    option = int_input("Select one of the menu items: ");
    if (option == 1)
    {
        cout << "Under repair status: " << pipe.in_repair << "\n";
        pipe.in_repair = bool_input("If you want to edit under repair status to in repair enter yes. If you want to edit under repair status to not in repair enter no.\n");
        cout << "Changed under repair status: " << pipe.in_repair << "\n";
    }
    else if (option == 0)
    {
        return;
    }
    else
    {
        cout << "Wrong menu item.\n";
    }
}

//show functions

void show_cs(const CS& cs, bool cs_exist)
{
    if (cs_exist == false)
    {
        cout << "The compressor station was not added yet. Add it first.\n";
        return;
    }
    cout << "Name: " << cs.name_cs << "\n";
    cout << "Amount of workshops: " << cs.amount_ws << "\n";
    cout << "Amount of workshops in progress: " << cs.amount_ws_in_progress << "\n";
    cout << "Class of compressor station: " << cs.class_cs << "\n";
}

void show_pipe(const Pipe& pipe, bool pipe_exist)
{
    if (pipe_exist == false)
    {
        cout << "The pipe was not added yet. Add it first.\n";
        return;
    }
    cout << "Kilometer mark (name): " << pipe.name_pipe << "\n";
    cout << "Length (km):  " << pipe.length << "\n";
    cout << "Diameter (mm): " << pipe.diam << "\n";
    cout << "Under repair status: " << pipe.in_repair << "\n";
}

// file

void save_pipe(ofstream& file, const Pipe& pipe, bool pipe_exist)
{
    file << pipe_exist << "\n";
    if (pipe_exist)
    {
        file << pipe.name_pipe << "\n";
        file << pipe.length << "\n";
        file << pipe.diam << "\n";
        file << pipe.in_repair << "\n";
    }
}

void save_cs(ofstream& file, const CS& cs, bool cs_exist)
{
    file << cs_exist << "\n";
    if (cs_exist)
    {
        file << cs.name_cs << "\n";
        file << cs.amount_ws << "\n";
        file << cs.amount_ws_in_progress << "\n";
        file << cs.class_cs << "\n";
    }
}

void save_data(const Pipe& pipe, bool pipe_exist, const CS& cs, bool cs_exist)
{
    string name_file;
    name_file = filename_input("Enter the name of the file where the data should be saved (if the file does not yet exist, enter the name and it will be created automatically): ");
    ofstream file(name_file);
    if (!file)
    {
        cout << "Cannot open file " << name_file << " for save data.\n";
        return;
    }

    save_pipe(file, pipe, pipe_exist);
    save_cs(file, cs, cs_exist);

    file.close();
    cout << "The data was saved in file " << name_file << "\n";
}

bool load_pipe(ifstream& file, Pipe& out_pipe, bool& out_pipe_exist)
{
    int pipe_flag;
    file >> pipe_flag;
    if (file.fail())
    {
        cout << "File corrupted (invalid pipe flag)!\n";
        return false;
    }
    file.ignore();

    if (pipe_flag == 1)
    {
        Pipe temp_pipe;
        getline(file, temp_pipe.name_pipe);
        file >> temp_pipe.length;
        file >> temp_pipe.diam;
        file >> temp_pipe.in_repair;
        if (file.fail())
        {
            cout << "File is corrupted (invalid pipe data).\n";
            return false;
        }
        if (temp_pipe.name_pipe == "" || temp_pipe.length <= 0 || temp_pipe.diam <= 0)
        {
            cout << "File contains invalid pipe values.\n";
            return false;
        }
        file.ignore();
        out_pipe = temp_pipe;
        out_pipe_exist = true;
    }
    else if (pipe_flag == 0)
    {
        out_pipe_exist = false;
    }
    else
    {
        cout << "File is corrupted (pipe flag must be 0 or 1).\n";
        return false;
    }
    return true;
}

bool load_cs(ifstream& file, CS& out_cs, bool& out_cs_exist)
{
    int cs_flag;
    file >> cs_flag;
    if (file.fail())
    {
        cout << "File is corrupted (invalid CS flag).\n";
        return false;
    }
    file.ignore();

    if (cs_flag == 1)
    {
        CS temp_cs;
        getline(file, temp_cs.name_cs);
        file >> temp_cs.amount_ws >> temp_cs.amount_ws_in_progress;
        if (file.fail())
        {
            cout << "File is corrupted (invalid CS data).\n";
            return false;
        }
        file.ignore();
        getline(file, temp_cs.class_cs);
        if (temp_cs.name_cs == "" || temp_cs.class_cs == "" || temp_cs.amount_ws < 0 || temp_cs.amount_ws_in_progress < 0 || temp_cs.amount_ws_in_progress > temp_cs.amount_ws)
        {
            cout << "File contains invalid CS values.\n";
            return false;
        }
        out_cs = temp_cs;
        out_cs_exist = true;
    }
    else if (cs_flag == 0)
    {
        out_cs_exist = false;
    }
    else
    {
        cout << "File is corrupted (CS flag must be 0 or 1).\n";
        return false;
    }
    return true;
}

void load_data(Pipe& pipe, bool& pipe_exist, CS& cs, bool& cs_exist)
{
    string name_file;
    name_file = filename_input("Enter the name of the file from which to load the data: ");
    ifstream file(name_file);
    if (!file)
    {
        cout << "File " << name_file << " not found!\n";
        return;
    }

    Pipe loaded_pipe;
    bool loaded_pipe_exist;
    CS loaded_cs;
    bool loaded_cs_exist;

    if (!load_pipe(file, loaded_pipe, loaded_pipe_exist))
    {
        return;
    }
    if (!load_cs(file, loaded_cs, loaded_cs_exist))
    {
        return;
    }

    file.close();
    pipe_exist = loaded_pipe_exist;
    cs_exist = loaded_cs_exist;
    if (loaded_pipe_exist) pipe = loaded_pipe;
    if (loaded_cs_exist) cs = loaded_cs;
    cout << "Data loaded from " << name_file << "\n";
}

// menu

void menu()
{
    cout << "\n\n 1. Add pipe\n";
    cout << " 2. Add cs\n";
    cout << " 3. View all objects\n";
    cout << " 4. Edit pipe\n";
    cout << " 5. Edit compressor station\n";
    cout << " 6. Save data to a file\n";
    cout << " 7. Load data from a file\n";
    cout << " 0. Exit\n";
}

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    bool pipe_exist = false;
    bool cs_exist = false;
    Pipe pipe;
    CS cs;

    int option;
    while (true)
    {
        menu();
        option = int_input("\nSelect one of the menu items: ");

        if (option == 1) add_pipe(pipe, pipe_exist);
        else if (option == 2) add_cs(cs, cs_exist);
        else if (option == 3) { show_cs(cs, cs_exist); show_pipe(pipe, pipe_exist); }
        else if (option == 4) edit_pipe(pipe, pipe_exist);
        else if (option == 5) edit_cs(cs, cs_exist);
        else if (option == 6) save_data(pipe, pipe_exist, cs, cs_exist);
        else if (option == 7) load_data(pipe, pipe_exist, cs, cs_exist);
        else if (option == 0)
        {
            break;
        }
        else
        {
            cout << "Wrong menu item.\n";
        }
    }
    return 0;
}
