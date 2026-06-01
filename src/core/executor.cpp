#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <sstream>
#include <cstring>
#include "../commands/cdEchoPwd.hpp"
#include "../features/history.hpp"
#include "../commands/pinfo.hpp"
#include "../utilities/search.hpp"
#include "../features/signals.hpp"
using namespace std;

bool execute_command(string cmd, bool background, vector<string> &history)
{
    istringstream iss(cmd);
    string command;
    iss >> command;

    if (command == "exit")
        return false;

    if (command == "cd" || command == "pwd" || command == "echo" || command == "history" || command == "pinfo" || command == "search")
    {
        if (background)
            cout << "Warning: builtin commands cannot be run in background\n";

        if (command == "cd")
        {
            string path;
            iss >> path;
            cd(path);
        }
        else if (command == "pwd")
        {
            pwd();
        }
        else if (command == "echo")
        {
            string rest;
            getline(iss, rest);

            while (!rest.empty() && rest.front() == ' ')
                rest.erase(rest.begin());

            while (!rest.empty() && rest.back() == ' ')
                rest.pop_back();

            echo(rest);
        }
        else if (command == "history")
        {
            display_history(history);
        }

        else if (command == "pinfo")
        {
            int pid;

            if (!(iss >> pid))
            {
                pid = getpid();
            }

            pinfo(pid);
        }
        else if (command == "search")
        {
            string name;

            if (!(iss >> name))
            {
                cout << "Usage: search <filename>" << endl;
            }
            else
            {
                bool found = search(name);

                cout << (found ? "True" : "False") << endl;
            }
        }
        return true;
    }

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return true;
    }

    if (pid == 0)
    {
        vector<char *> args;
        istringstream iss2(cmd);
        string token;
        while (iss2 >> token)
            args.push_back(strdup(token.c_str()));
        args.push_back(nullptr);

        execvp(args[0], args.data());
        perror("execvp");
        for (char *arg : args)
            free(arg);
        exit(EXIT_FAILURE);
    }
    else
    {
        if (!background)
        {
            foreground_pid = pid;

            waitpid(pid, nullptr, 0);

            foreground_pid = -1;
        }

        else
        {
            cout << "Background PID: " << pid << endl;
        }
    }
    return true;
}