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

        // Exit condition for testing
        if (command == "exit")
        {
            break; // Exit the loop
        }

        if (command.find('|') != string::npos)
        {
            execute_pipeline(command);
        }
        else if (command.find('>') != string::npos || command.find('<') != string::npos)
        {
            execute_command_with_redirection(command);
        }
        else
        {
            execute_command(command, false);
        }
    }
    return 0; // Return success
}
