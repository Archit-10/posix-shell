#include <iostream>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include "executor.hpp"
using namespace std;

void execute_pipeline(string cmd, vector<string> &history)
{
    istringstream iss(cmd);
    vector<string> commands;
    string segment;

    if (!cmd.empty() && cmd.back() == '\n')
        cmd.pop_back();

    // Split by pipe
    while (getline(iss, segment, '|'))
    {
        size_t start = segment.find_first_not_of(" \t");
        size_t end = segment.find_last_not_of(" \t");

        if (start == string::npos)
            continue;

        segment = segment.substr(start, end - start + 1);

        commands.push_back(segment);
    }

    int n = commands.size();
    if (n == 0)
        return;

    std::vector<int> pipefds(2 * (n - 1));

    for (int i = 0; i < n - 1; i++)
    {
        if (pipe(&pipefds[i * 2]) < 0)
        {
            perror("pipe");
            return;
        }
    }

    for (int i = 0; i < n; i++)
    {
        pid_t pid = fork();

        if (pid == 0)
        {
            // input from previous pipe
            if (i > 0)
            {
                dup2(pipefds[(i - 1) * 2], 0);
            }

            // output to next pipe
            if (i < n - 1)
            {
                dup2(pipefds[i * 2 + 1], 1);
            }

            // close all pipe fds
            for (int j = 0; j < 2 * (n - 1); j++)
            {
                close(pipefds[j]);
            }

            // execute single command using executor
            execute_command(commands[i], false, history);

            exit(0);
        }
        else if (pid < 0)
        {
            perror("fork");
            return;
        }
    }

    // parent closes pipes
    for (int i = 0; i < 2 * (n - 1); i++)
    {
        close(pipefds[i]);
    }

    // wait children
    for (int i = 0; i < n; i++)
    {
        wait(nullptr);
    }
}