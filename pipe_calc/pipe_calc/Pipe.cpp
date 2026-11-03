#include <iostream>
#include <string>
#include <fstream>

#include "Pipe.h"
#include "utils.h"

using namespace std;

// addition function

void add_pipe(unordered_map<int, Pipe>& pipes)
{
    Pipe pipe;
    pipe.id = next_id(pipes);
    cout << "\nEnter the data for the pipe:\n";
    pipe.name_pipe = string_input("Kilometer mark (name): ");
    pipe.length = double_input("Length (km): ");
    pipe.diam = int_input("Diameter (mm): ", 1);
    pipe.in_repair = bool_input("Under repair status");
    pipes.emplace(pipe.id, pipe);
    cout << "Pipe added! ID: " << pipe.id << "\n";
    log_action("Added pipe ID " + to_string(pipe.id) + " " + pipe.name_pipe);
}

// search function

unordered_set<int> find_pipes(const unordered_map<int, Pipe>& pipes)
{
    unordered_set<int> found;
    int option;
    cout << "1. Search by name\n";
    cout << "2. Search by repair status\n";
    cout << "3. All pipes\n";
    cout << "0. Cancel\n";
    option = int_input("Select filter: ", 0, 3);
    if (option == 0) return found;

    string name;
    bool status = false;
    if (option == 1) name = string_input("Enter part of the name: ");
    if (option == 2) status = bool_input("Search pipes under repair");

    for (int id : sorted_keys(pipes))
    {
        const Pipe& pipe = pipes.at(id);
        if (option == 3 || (option == 1 && pipe.name_pipe.find(name) != string::npos) || (option == 2 && pipe.in_repair == status))
        {
            found.insert(id);
            show_pipe(pipe);
        }
    }
    if (found.empty())
    {
        cout << "No pipes found.\n";
    }
    log_action("Pipe search, filter " + to_string(option) + ", found IDs: " + ids_to_string(found));
    return found;
}

// editing function

void edit_pipes(unordered_map<int, Pipe>& pipes)
{
    unordered_set<int> found = find_pipes(pipes);
    if (found.empty()) return;

    int option;
    cout << "1. Edit under repair status\n";
    cout << "2. Delete\n";
    cout << "0. Cancel\n";
    option = int_input("Select one of the menu items: ", 0, 2);
    if (option == 0) return;

    unordered_set<int> ids = choose_ids(found);
    if (ids.empty()) return;

    if (option == 1)
    {
        bool status;
        status = bool_input("Set under repair status to");
        for (int id : ids) pipes.at(id).in_repair = status;
        if (status) log_action("Repair status of pipes " + ids_to_string(ids) + "set to yes");
        else log_action("Repair status of pipes " + ids_to_string(ids) + "set to no");
    }
    else if (option == 2)
    {
        for (int id : ids) pipes.erase(id);
        log_action("Deleted pipes " + ids_to_string(ids));
    }
    cout << "Done.\n";
}

// show functions

void show_pipe(const Pipe& pipe)
{
    cout << "ID " << pipe.id << " | " << pipe.name_pipe << " | length: " << pipe.length << " km | diameter: " << pipe.diam << " mm | in repair: ";
    if (pipe.in_repair) cout << "yes\n";
    else cout << "no\n";
}

void show_all_pipes(const unordered_map<int, Pipe>& pipes)
{
    if (pipes.empty())
    {
        cout << "No pipes yet.\n";
        return;
    }
    for (int id : sorted_keys(pipes)) show_pipe(pipes.at(id));
}

// file

void save_pipes(ofstream& file, const unordered_map<int, Pipe>& pipes)
{
    file << pipes.size() << "\n";
    for (int id : sorted_keys(pipes))
    {
        const Pipe& pipe = pipes.at(id);
        file << pipe.id << "\n";
        file << pipe.name_pipe << "\n";
        file << pipe.length << "\n";
        file << pipe.diam << "\n";
        file << pipe.in_repair << "\n";
    }
}

bool load_pipes(ifstream& file, unordered_map<int, Pipe>& pipes)
{
    int count;
    file >> count;
    if (file.fail() || count < 0)
    {
        return false;
    }

    for (int i = 0; i < count; i++)
    {
        Pipe temp_pipe;
        file >> temp_pipe.id;
        getline(file >> ws, temp_pipe.name_pipe);
        file >> temp_pipe.length;
        file >> temp_pipe.diam;
        file >> temp_pipe.in_repair;
        if (file.fail())
        {
            return false;
        }
        if (temp_pipe.id < 1 || temp_pipe.name_pipe == "" || temp_pipe.length <= 0 || temp_pipe.diam <= 0 || pipes.count(temp_pipe.id) != 0)
        {
            return false;
        }
        pipes.emplace(temp_pipe.id, temp_pipe);
    }
    return true;
}
