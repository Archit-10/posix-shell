#include <iostream>
#include <string>

#include "../core/executor.hpp"
#include "../core/pipeline.hpp"
#include "../core/IO_redirection.hpp"
using namespace std;

void displayPrompt();
int main()
{
    // Testing displayPrompt()
    while (true)
    {
        displayPrompt();

        string command;
        getline(cin, command);

        bool background = false;

        if (!command.empty() && command.back() == '&')
        {
            background = true;
            command.pop_back();
        }

        if (command.find('|') != string::npos)
        {
            execute_pipeline(command);
        }
        else if (command.find('>') != string::npos || command.find('<') != string::npos)
        {
            execute_command_with_redirection(command);
        }
        else if (!execute_command(command, background))
            break;
    }
    return 0; // Return success
}
