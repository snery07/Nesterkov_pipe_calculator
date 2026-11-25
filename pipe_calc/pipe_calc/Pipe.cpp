#include <iostream>
#include <string>
#include <fstream>

#include "Pipe.h"
#include "utils.h"

using namespace std;

// getters and setters

int Pipe::get_id() const
{
    return id;
}

string Pipe::get_name() const
{
    return name_pipe;
}

bool Pipe::get_in_repair() const
{
    return in_repair;
}

void Pipe::set_in_repair(bool status)
{
    in_repair = status;
}

// input and show

void Pipe::input(int new_id)
{
    id = new_id;
    cout << "\nEnter the data for the pipe:\n";
    name_pipe = string_input("Kilometer mark (name): ");
    length = double_input("Length (km): ");
    diam = int_input("Diameter (mm): ", 1);
    in_repair = bool_input("Under repair status");
}

void Pipe::show() const
{
    cout << "ID " << id << " | " << name_pipe << " | length: " << length << " km | diameter: " << diam << " mm | in repair: ";
    if (in_repair)
        cout << "yes\n";
    else
        cout << "no\n";
}

// file

void Pipe::save(ofstream& file) const
{
    file << id << "\n";
    file << name_pipe << "\n";
    file << length << "\n";
    file << diam << "\n";
    file << in_repair << "\n";
}

bool Pipe::load(ifstream& file)
{
    file >> id;
    getline(file >> ws, name_pipe);
    file >> length;
    file >> diam;
    file >> in_repair;
    if (file.fail())
    {
        return false;
    }
    if (id < 1 || name_pipe == "" || length <= 0 || diam <= 0)
    {
        return false;
    }
    return true;
}

// addition function

void add_pipe(unordered_map<int, Pipe>& pipes)
{
    Pipe pipe;
    pipe.input(next_id(pipes));
    pipes.emplace(pipe.get_id(), pipe);
    cout << "Pipe added! ID: " << pipe.get_id() << "\n";
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
        if (option == 3 || (option == 1 && pipe.get_name().find(name) != string::npos) || (option == 2 && pipe.get_in_repair() == status))
        {
            found.emplace(id);
            pipe.show();
        }
    }
    if (found.empty())
    {
        cout << "No pipes found.\n";
    }
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
        for (int id : ids)
            pipes.at(id).set_in_repair(status);
    }
    else if (option == 2)
    {
        for (int id : ids) pipes.erase(id);
    }
    cout << "Done.\n";
}

// show functions

void show_all_pipes(const unordered_map<int, Pipe>& pipes)
{
    if (pipes.empty())
    {
        cout << "No pipes yet.\n";
        return;
    }
    for (int id : sorted_keys(pipes))
        pipes.at(id).show();
}

// file

void save_pipes(ofstream& file, const unordered_map<int, Pipe>& pipes)
{
    file << pipes.size() << "\n";
    for (int id : sorted_keys(pipes))
        pipes.at(id).save(file);
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
        if (!temp_pipe.load(file) || pipes.count(temp_pipe.get_id()) != 0)
        {
            return false;
        }
        pipes.emplace(temp_pipe.get_id(), temp_pipe);
    }
    return true;
}
