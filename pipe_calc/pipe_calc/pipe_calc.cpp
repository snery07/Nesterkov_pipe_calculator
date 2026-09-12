#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

struct Pipe
{
    string name_p;
    int diam;
    double length;
};

struct CS
{
    string name_cs;
    int amount_ws;
    int amount_ws_in_progress;
    string class_cs;
};

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    cout << " 1. Add pipe\n";
    cout << " 2. Add cs\n";
    cout << " 3. View all objects\n";
    cout << " 4. Edit pipe\n";
    cout << " 5. Edit compressor station\n";
    cout << " 6. Save\n";
    cout << " 7. Load\n";
    cout << " 0. Exit\n";
}
