#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <unordered_map>

#include "Pipe.h"
#include "CS.h"
#include "utils.h"

using namespace std;

// show function

void show_all(const unordered_map<int, Pipe>& pipes, const unordered_map<int, CS>& stations)
{
    show_all_pipes(pipes);
    show_all_stations(stations);
}

// file

void save_data(const unordered_map<int, Pipe>& pipes, const unordered_map<int, CS>& stations)
{
    string name_file;
    name_file = filename_input("Enter the name of the file where the data should be saved: ");
    ofstream file(name_file);
    if (!file)
    {
        log_error("Cannot open file " + name_file + " for save data.");
        return;
    }

    save_pipes(file, pipes);
    save_stations(file, stations);

    file.close();
    if (file.fail())
    {
        log_error("Error while writing to file " + name_file + ". The data may be incomplete.");
        return;
    }
    cout << "The data was saved in file " << name_file << "\n";
    log_action("Saved to file " + name_file);
}

void load_data(unordered_map<int, Pipe>& pipes, unordered_map<int, CS>& stations)
{
    string name_file;
    name_file = filename_input("Enter the name of the file from which to load the data: ");
    ifstream file(name_file);
    if (!file)
    {
        log_error("File " + name_file + " not found!");
        return;
    }

    unordered_map<int, Pipe> loaded_pipes;
    unordered_map<int, CS> loaded_stations;

    if (!load_pipes(file, loaded_pipes) || !load_stations(file, loaded_stations))
    {
        log_error("File " + name_file + " is corrupted. The data was not loaded.");
        return;
    }

    file.close();
    pipes = loaded_pipes;
    stations = loaded_stations;
    cout << "Data loaded from " << name_file << "\n";
    log_action("Loaded from file " + name_file);
}

// menu

void menu()
{
    cout << "\n\n 1. Add pipe\n";
    cout << " 2. Add cs\n";
    cout << " 3. View all objects\n";
    cout << " 4. Search pipes\n";
    cout << " 5. Search compressor stations\n";
    cout << " 6. Edit / delete pipes\n";
    cout << " 7. Edit / delete compressor stations\n";
    cout << " 8. Save data to a file\n";
    cout << " 9. Load data from a file\n";
    cout << " 0. Exit\n";
}

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    unordered_map<int, Pipe> pipes;
    unordered_map<int, CS> stations;
    log_action("Program started");

    int option;
    while (true)
    {
        menu();
        option = int_input("\nSelect one of the menu items: ", 0, 9);
        log_action("Menu item " + to_string(option));

        if (option == 1) add_pipe(pipes);
        else if (option == 2) add_cs(stations);
        else if (option == 3) show_all(pipes, stations);
        else if (option == 4) find_pipes(pipes);
        else if (option == 5) find_stations(stations);
        else if (option == 6) edit_pipes(pipes);
        else if (option == 7) edit_stations(stations);
        else if (option == 8) save_data(pipes, stations);
        else if (option == 9) load_data(pipes, stations);
        else if (option == 0) break;
    }

    log_action("Program finished");
    return 0;
}
