#pragma once

#include <string>
#include <fstream>
#include <map>
#include <set>

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
void add_cs(map<int, CS>& stations);
set<int> find_stations(const map<int, CS>& stations);
void edit_stations(map<int, CS>& stations);

// show functions
void show_cs(const CS& cs);
void show_all_stations(const map<int, CS>& stations);

// file
void save_stations(ofstream& file, const map<int, CS>& stations);
bool load_stations(ifstream& file, map<int, CS>& stations);
