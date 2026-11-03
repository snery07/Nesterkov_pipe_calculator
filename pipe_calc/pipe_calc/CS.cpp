#include <iostream>
#include <string>
#include <fstream>

#include "CS.h"
#include "utils.h"

using namespace std;

double idle_percent(const CS& cs)
{
    return 100.0 * (cs.amount_ws - cs.amount_ws_in_progress) / cs.amount_ws;
}

// addition function

void add_cs(map<int, CS>& stations)
{
    CS cs;
    cs.id = next_id(stations);
    cout << "\nEnter the data for the compressor station:\n";
    cs.name_cs = string_input("Name: ");
    cs.amount_ws = int_input("Amount of workshops: ", 1);
    cs.amount_ws_in_progress = int_input("Amount of workshops in progress: ", 0, cs.amount_ws);
    cs.class_cs = string_input("Class of compressor station: ");
    stations.emplace(cs.id, cs);
    cout << "Compressor station added! ID: " << cs.id << "\n";
    log_action("Added CS ID " + to_string(cs.id) + " " + cs.name_cs);
}

// search function (shows the found stations and returns their IDs)

set<int> find_stations(const map<int, CS>& stations)
{
    set<int> found;
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
    if (option == 1) name = string_input("Enter part of the name: ");
    if (option == 2)
    {
        min_percent = int_input("Minimum percent of idle workshops: ", 0, 100);
        max_percent = int_input("Maximum percent of idle workshops: ", min_percent, 100);
    }

    for (const auto& item : stations)
    {
        const CS& cs = item.second;
        if (option == 3 || (option == 1 && cs.name_cs.find(name) != string::npos) || (option == 2 && idle_percent(cs) >= min_percent && idle_percent(cs) <= max_percent))
        {
            found.insert(cs.id);
            show_cs(cs);
        }
    }
    if (found.empty())
    {
        cout << "No compressor stations found.\n";
    }
    log_action("CS search, filter " + to_string(option) + ", found IDs: " + ids_to_string(found));
    return found;
}   

// editing functions

bool start_workshop(CS& cs, int amount_ws)
{
    if (amount_ws > (cs.amount_ws - cs.amount_ws_in_progress))
    {
        return false;
    }
    cs.amount_ws_in_progress += amount_ws;
    return true;
}

bool stop_workshop(CS& cs, int amount_ws)
{
    if (amount_ws > cs.amount_ws_in_progress)
    {
        return false;
    }
    cs.amount_ws_in_progress -= amount_ws;
    return true;
}

void edit_stations(map<int, CS>& stations)
{
    set<int> found = find_stations(stations);
    if (found.empty()) return;

    int option;
    cout << "1. Start workshops\n";
    cout << "2. Stop workshops\n";
    cout << "3. Delete\n";
    cout << "0. Cancel\n";
    option = int_input("Select one of the menu items: ", 0, 3);
    if (option == 0) return;

    set<int> ids = choose_ids(found);
    if (ids.empty()) return;

    if (option == 3)
    {
        for (int id : ids) stations.erase(id);
        log_action("Deleted CS " + ids_to_string(ids));
    }
    else
    {
        int amount_ws;
        amount_ws = int_input("Amount of workshops (for each chosen station): ", 1);
        for (int id : ids)
        {
            CS& cs = stations.at(id);
            bool done;
            if (option == 1) done = start_workshop(cs, amount_ws);
            else done = stop_workshop(cs, amount_ws);

            if (done == false)
            {
                log_error("CS " + to_string(cs.id) + ": not enough workshops, skipped.");
            }
            else
            {
                cout << "CS " << cs.id << ": workshops in progress " << cs.amount_ws_in_progress << "/" << cs.amount_ws << "\n";
                log_action("CS " + to_string(cs.id) + " workshops in progress " + to_string(cs.amount_ws_in_progress));
            }
        }
    }
    cout << "Done.\n";
}

// show functions

void show_cs(const CS& cs)
{
    cout << "ID " << cs.id << " | " << cs.name_cs << " | workshops in progress: " << cs.amount_ws_in_progress << "/" << cs.amount_ws << " | idle: " << idle_percent(cs) << "% | class: " << cs.class_cs << "\n";
}

void show_all_stations(const map<int, CS>& stations)
{
    if (stations.empty())
    {
        cout << "No compressor stations yet.\n";
        return;
    }
    for (const auto& item : stations) show_cs(item.second);
}

// file

void save_stations(ofstream& file, const map<int, CS>& stations)
{
    file << stations.size() << "\n";
    for (const auto& item : stations)
    {
        const CS& cs = item.second;
        file << cs.id << "\n";
        file << cs.name_cs << "\n";
        file << cs.amount_ws << "\n";
        file << cs.amount_ws_in_progress << "\n";
        file << cs.class_cs << "\n";
    }
}

bool load_stations(ifstream& file, map<int, CS>& stations)
{
    int count;
    file >> count;
    if (file.fail() || count < 0)
    {
        return false;
    }

    for (int i = 0; i < count; i++)
    {
        CS temp_cs;
        file >> temp_cs.id;
        getline(file >> ws, temp_cs.name_cs);
        file >> temp_cs.amount_ws >> temp_cs.amount_ws_in_progress;
        getline(file >> ws, temp_cs.class_cs);
        if (file.fail())
        {
            return false;
        }
        if (temp_cs.id < 1 || temp_cs.name_cs == "" || temp_cs.class_cs == "" || temp_cs.amount_ws < 1 || temp_cs.amount_ws_in_progress < 0 || temp_cs.amount_ws_in_progress > temp_cs.amount_ws || stations.count(temp_cs.id) != 0)
        {
            return false;
        }
        stations.emplace(temp_cs.id, temp_cs);
    }
    return true;
}
