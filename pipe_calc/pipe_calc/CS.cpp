#include <iostream>
#include <string>
#include <fstream>

#include "CS.h"
#include "utils.h"

using namespace std;

// getters

int CS::get_id() const
{
    return id;
}

string CS::get_name() const
{
    return name_cs;
}

int CS::get_amount_ws() const
{
    return amount_ws;
}

int CS::get_amount_ws_in_progress() const
{
    return amount_ws_in_progress;
}

double CS::idle_percent() const
{
    return 100.0 * (amount_ws - amount_ws_in_progress) / amount_ws;
}

// workshops

bool CS::start_workshops(int amount)
{
    if (amount > (amount_ws - amount_ws_in_progress))
        return false;
    amount_ws_in_progress += amount;
    return true;
}

bool CS::stop_workshops(int amount)
{
    if (amount > amount_ws_in_progress)
        return false;
    amount_ws_in_progress -= amount;
    return true;
}

// input and show

void CS::input(int new_id)
{
    id = new_id;
    cout << "\nEnter the data for the compressor station:\n";
    name_cs = string_input("Name: ");
    amount_ws = int_input("Amount of workshops: ", 1);
    amount_ws_in_progress = int_input("Amount of workshops in progress: ", 0, amount_ws);
    class_cs = string_input("Class of compressor station: ");
}

void CS::show() const
{
    cout << "ID " << id << " | " << name_cs << " | workshops in progress: " << amount_ws_in_progress << "/" << amount_ws << " | idle: " << idle_percent() << "% | class: " << class_cs << "\n";
}

// file

void CS::save(ofstream& file) const
{
    file << id << "\n";
    file << name_cs << "\n";
    file << amount_ws << "\n";
    file << amount_ws_in_progress << "\n";
    file << class_cs << "\n";
}

bool CS::load(ifstream& file)
{
    file >> id;
    getline(file >> ws, name_cs);
    file >> amount_ws >> amount_ws_in_progress;
    getline(file >> ws, class_cs);
    if (file.fail())
        return false;
    if (id < 1 || name_cs == "" || class_cs == "" || amount_ws < 1 || amount_ws_in_progress < 0 || amount_ws_in_progress > amount_ws)
        return false;
    return true;
}

// addition function

void add_cs(unordered_map<int, CS>& stations)
{
    CS cs;
    cs.input(next_id(stations));
    stations.emplace(cs.get_id(), cs);
    cout << "Compressor station added! ID: " << cs.get_id() << "\n";
}

// search function (shows the found stations and returns their IDs)

unordered_set<int> find_stations(const unordered_map<int, CS>& stations)
{
    unordered_set<int> found;
    int option;
    cout << "1. Search by name\n";
    cout << "2. Search by percent of idle workshops\n";
    cout << "3. All compressor stations\n";
    cout << "0. Cancel\n";
    option = int_input("Select filter: ", 0, 3);
    if (option == 0) return found;

    string name;
    int min_percent = 0;
    int max_percent = 100;
    if (option == 1)
        name = string_input("Enter part of the name: ");
    if (option == 2)
    {
        min_percent = int_input("Minimum percent of idle workshops: ", 0, 100);
        max_percent = int_input("Maximum percent of idle workshops: ", min_percent, 100);
    }

    for (int id : sorted_keys(stations))
    {
        const CS& cs = stations.at(id);
        if (option == 3 || (option == 1 && cs.get_name().find(name) != string::npos) || (option == 2 && cs.idle_percent() >= min_percent && cs.idle_percent() <= max_percent))
        {
            found.emplace(id);
            cs.show();
        }
    }
    if (found.empty())
        cout << "No compressor stations found.\n";
    return found;
}

// editing function

void edit_stations(unordered_map<int, CS>& stations)
{
    unordered_set<int> found = find_stations(stations);
    if (found.empty()) return;

    int option;
    cout << "1. Start workshops\n";
    cout << "2. Stop workshops\n";
    cout << "3. Delete\n";
    cout << "0. Cancel\n";
    option = int_input("Select one of the menu items: ", 0, 3);
    if (option == 0) return;

    unordered_set<int> ids = choose_ids(found);
    if (ids.empty()) 
        return;

    if (option == 3)
    {
        for (int id : ids) stations.erase(id);
    }
    else
    {
        int amount_ws;
        amount_ws = int_input("Amount of workshops (for each chosen station): ", 1);
        for (int id : sorted_ids(ids))
        {
            CS& cs = stations.at(id);
            bool done;
            if (option == 1) done = cs.start_workshops(amount_ws);
            else done = cs.stop_workshops(amount_ws);

            if (done == false)
                cout << "CS " << cs.get_id() << ": not enough workshops, skipped.\n";
            else
                cout << "CS " << cs.get_id() << ": workshops in progress " << cs.get_amount_ws_in_progress() << "/" << cs.get_amount_ws() << "\n";
        }
    }
    cout << "Done.\n";
}

// show functions

void show_all_stations(const unordered_map<int, CS>& stations)
{
    if (stations.empty())
    {
        cout << "No compressor stations yet.\n";
        return;
    }
    for (int id : sorted_keys(stations)) 
        stations.at(id).show();
}

// file

void save_stations(ofstream& file, const unordered_map<int, CS>& stations)
{
    file << stations.size() << "\n";
    for (int id : sorted_keys(stations)) 
        stations.at(id).save(file);
}

bool load_stations(ifstream& file, unordered_map<int, CS>& stations)
{
    int count;
    file >> count;
    if (file.fail() || count < 0)
        return false;

    for (int i = 0; i < count; i++)
    {
        CS temp_cs;
        if (!temp_cs.load(file) || stations.count(temp_cs.get_id()) != 0)
            return false;
        stations.emplace(temp_cs.get_id(), temp_cs);
    }
    return true;
}
