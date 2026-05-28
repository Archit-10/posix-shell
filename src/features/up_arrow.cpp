#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
    DISPLAY HISTORY (SAFE INDEXING)
*/
void display_history(const vector<string> &history, int num)
{
    size_t size = history.size();

    size_t start = (size > (size_t)num) ? (size - num) : 0;

    for (size_t i = start; i < size; ++i)
    {
        cout << history[i] << endl;
    }
}

/*
    READ COMMAND WITH ARROW NAVIGATION (SIMPLIFIED SAFE VERSION)
    NOTE: Assumes index is controlled externally
*/
void read_command_with_arrows(vector<string> &history)
{
    int index = (int)history.size(); // current cursor position
    string current_command = "";

    // NOTE: arrow-key handling logic is typically terminal dependent
    // Keeping only safe boundary logic here

    // Example safe access pattern:
    if (!history.empty())
    {
        if (index < 0)
            index = 0;

        if (index >= 0 && (size_t)index < history.size())
        {
            current_command = history[index];
        }
        else
        {
            current_command = "";
        }
    }

    cout << current_command;
}