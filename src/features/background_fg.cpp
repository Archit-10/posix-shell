#include <iostream>
#include <sstream>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fstream>
#include <cstring>

using namespace std;

void foreground(string &cmd)
{
    pid_t child_pid = fork();

    if (child_pid == -1)
    {
        perror("Error: fork");
        return;
    }

    if (child_pid == 0)
    {
        vector<char *> v;
        istringstream iss(cmd);
        string s;
        while (iss >> s)
        {
            v.push_back(strdup(s.c_str()));
        }
        v.push_back(nullptr);

        if (execvp(v[0], v.data()) == -1)
        {
            perror("Error: execvp");
            for (auto arg : v)
                free(arg);
            exit(EXIT_FAILURE);
        }
        for (auto arg : v)
            free(arg);
    }
    else
    {
        int value;
        waitpid(child_pid, &value, 0);
    }
}
void background(string &cmd)
{
    pid_t child_pid = fork();

    if (child_pid == -1)
    {
        perror("fork");
        return;
    }

    if (child_pid == 0)
    {
        vector<char *> v;
        istringstream iss(cmd);
        string s;

        while (iss >> s)
        {
            v.push_back(strdup(s.c_str()));
        }
        v.push_back(nullptr);

        if (execvp(v[0], v.data()) == -1)
        {
            perror("execvp");

            for (auto arg : v)
            {
                free(arg);
            }

            exit(EXIT_FAILURE);
        }

        for (auto arg : v)
        {
            free(arg);
        }
    }
    else
    {
        cout << "Background PID: " << child_pid << endl;
    }
}

void execute_external_command(const string &cmd)
{
    pid_t child_pid = fork();

    if (child_pid == -1)
    {
        perror("fork");
        return;
    }

    if (child_pid == 0)
    {
        vector<char *> v;
        istringstream iss(cmd);

        string arg;
        while (iss >> arg)
        {
            v.push_back(strdup(arg.c_str()));
        }
        v.push_back(nullptr);

        if (execvp(v[0], v.data()) == -1)
        {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        int status;
        waitpid(child_pid, &status, 0);
    }
}
