#pragma once

#include <string>
#include <fstream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Pipe
{
private:
    int id = 0;
    string name_pipe = "";
    int diam = 0;
    double length = 0;
    bool in_repair = false;

public:
    // getters and setters
    int get_id() const;
    string get_name() const;
    bool get_in_repair() const;
    void set_in_repair(bool status);

    // input and show
    void input(int new_id);
    void show() const;

    // file (load returns false if the data in the file is wrong)
    void save(ofstream& file) const;
    bool load(ifstream& file);
};

// addition, search and editing functions
void add_pipe(unordered_map<int, Pipe>& pipes);
unordered_set<int> find_pipes(const unordered_map<int, Pipe>& pipes);
void edit_pipes(unordered_map<int, Pipe>& pipes);

// show functions
void show_all_pipes(const unordered_map<int, Pipe>& pipes);

// file
void save_pipes(ofstream& file, const unordered_map<int, Pipe>& pipes);
bool load_pipes(ifstream& file, unordered_map<int, Pipe>& pipes);
