#pragma once

#include <string>
#include <fstream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct Pipe
{
    int id;
    string name_pipe;
    int diam;
    double length;
    bool in_repair;
};

// addition, search and editing functions
void add_pipe(unordered_map<int, Pipe>& pipes);
unordered_set<int> find_pipes(const unordered_map<int, Pipe>& pipes);
void edit_pipes(unordered_map<int, Pipe>& pipes);

// show functions
void show_pipe(const Pipe& pipe);
void show_all_pipes(const unordered_map<int, Pipe>& pipes);

// file
void save_pipes(ofstream& file, const unordered_map<int, Pipe>& pipes);
bool load_pipes(ifstream& file, unordered_map<int, Pipe>& pipes);
