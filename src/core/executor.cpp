#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <sstream>
#include <cstring>
#include "../commands/cdEchoPwd.hpp"
using namespace std;

bool execute_command(string cmd, bool background)
{
    istringstream iss(cmd);
    string command;
    iss >> command;

    if (command == "exit")
        return false;

    if (command == "cd" || command == "pwd" || command == "echo")
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
            echo(rest);
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
            waitpid(pid, nullptr, 0);
        else
            cout << "Background PID: " << pid << endl;
    }
    return true;
}