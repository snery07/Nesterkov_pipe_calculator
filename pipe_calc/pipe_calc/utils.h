#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// log
void log_action(string text);
void log_error(string text);

// replay of all inputs from a log file (false if the file is not found or has no actions)
bool start_replay(string name_file);

// functions for check input
int int_input(string message, int min_value = 0, int max_value = 1000000);
double double_input(string message);
bool bool_input(string message);
string string_input(string message);

// helpers (IDs are sorted so the order is always the same)
vector<int> sorted_ids(const unordered_set<int>& ids);
string ids_to_string(const unordered_set<int>& ids);
unordered_set<int> choose_ids(const unordered_set<int>& found);

// templates
template <typename T>
vector<int> sorted_keys(const unordered_map<int, T>& items)
{
    vector<int> result;
    for (const auto& item : items)
        result.push_back(item.first);
    sort(result.begin(), result.end());
    return result;
}

template <typename T>
int next_id(const unordered_map<int, T>& items)
{
    int id = 1;
    for (const auto& item : items)
    {
        if (item.first >= id)
            id = item.first + 1;
    }
    return id;
}
