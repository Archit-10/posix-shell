#include <iostream>
#include <string>
#include <vector>

#include "../core/executor.hpp"
#include "../core/pipeline.hpp"
#include "../core/IO_redirection.hpp"
#include "../features/history.hpp"
#include "../features/signals.hpp"
using namespace std;

void displayPrompt();

int main()
{
    vector<string> history;

    load_history(history);
    setup_signal_handlers();

    while (true)
    {
        displayPrompt();

        string command;
        getline(cin, command);

        if (!command.empty())
        {
            add_command_to_history(history, command);
        }

        bool background = false;

        if (!command.empty() && command.back() == '&')
        {
            background = true;
            command.pop_back();
        }

        if (command.find('|') != string::npos)
        {
            execute_pipeline(command, history);
        }
        else if (command.find('>') != string::npos ||
                 command.find('<') != string::npos)
        {
            execute_command_with_redirection(command);
        }
        else if (!execute_command(command,
                                  background,
                                  history))
        {
            break;
        }
    }

    return 0;
}