#pragma once

#include <string>
#include <map>
#include <set>

using namespace std;

// log
void log_action(string text);
void log_error(string text);

// functions for check input
int int_input(string message, int min_value = 0, int max_value = 1000000);
double double_input(string message);
bool bool_input(string message);
string string_input(string message);
string filename_input(string message);

// helpers
string ids_to_string(const set<int>& ids);
set<int> choose_ids(const set<int>& found);

// templates
// map is sorted by ID, so the last element has the biggest ID
template <typename T>
int next_id(const map<int, T>& items)
{
    if (items.empty()) return 1;
    return items.rbegin()->first + 1;
}
