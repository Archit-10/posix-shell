#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <sstream>
#include <cstring>

using namespace std;

void execute_command(string cmd, bool background)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return;
    }

    if (pid == 0)
    {
        vector<char *> args;
        istringstream iss(cmd);
        string token;

        while (iss >> token)
        {
            args.push_back(strdup(token.c_str()));
        }

        args.push_back(nullptr);

        execvp(args[0], args.data());

        perror("execvp");
        exit(EXIT_FAILURE);
    }
    else
    {
        if (!background)
            waitpid(pid, nullptr, 0);
        else
            cout << "Background PID: " << pid << endl;
    }
}