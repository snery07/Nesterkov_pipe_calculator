#pragma once

#include <string>
#include <fstream>
#include <map>
#include <set>

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
void add_pipe(map<int, Pipe>& pipes);
set<int> find_pipes(const map<int, Pipe>& pipes);
void edit_pipes(map<int, Pipe>& pipes);

// show functions
void show_pipe(const Pipe& pipe);
void show_all_pipes(const map<int, Pipe>& pipes);

// file
void save_pipes(ofstream& file, const map<int, Pipe>& pipes);
bool load_pipes(ifstream& file, map<int, Pipe>& pipes);
