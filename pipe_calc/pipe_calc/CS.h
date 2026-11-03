#pragma once

#include <string>
#include <fstream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct CS
{
    int id;
    string name_cs;
    int amount_ws;
    int amount_ws_in_progress;
    string class_cs;
};

double idle_percent(const CS& cs);

// addition, search and editing functions
void add_cs(unordered_map<int, CS>& stations);
unordered_set<int> find_stations(const unordered_map<int, CS>& stations);
void edit_stations(unordered_map<int, CS>& stations);

// show functions
void show_cs(const CS& cs);
void show_all_stations(const unordered_map<int, CS>& stations);

// file
void save_stations(ofstream& file, const unordered_map<int, CS>& stations);
bool load_stations(ifstream& file, unordered_map<int, CS>& stations);
