#pragma once

#include <string>
#include <fstream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class CS
{
private:
    int id = 0;
    string name_cs = "";
    int amount_ws = 0;
    int amount_ws_in_progress = 0;
    string class_cs = "";

public:
    // getters
    int get_id() const;
    string get_name() const;
    int get_amount_ws() const;
    int get_amount_ws_in_progress() const;
    double idle_percent() const;

    // workshops (return false if there are not enough workshops)
    bool start_workshops(int amount);
    bool stop_workshops(int amount);

    // input and show
    void input(int new_id);
    void show() const;

    // file (load returns false if the data in the file is wrong)
    void save(ofstream& file) const;
    bool load(ifstream& file);
};

// addition, search and editing functions
void add_cs(unordered_map<int, CS>& stations);
unordered_set<int> find_stations(const unordered_map<int, CS>& stations);
void edit_stations(unordered_map<int, CS>& stations);

// show functions
void show_all_stations(const unordered_map<int, CS>& stations);

// file
void save_stations(ofstream& file, const unordered_map<int, CS>& stations);
bool load_stations(ifstream& file, unordered_map<int, CS>& stations);
