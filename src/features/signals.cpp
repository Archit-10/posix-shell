#include <iostream>
#include <sstream>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>
#include <csignal>
#include "signals.hpp"
using namespace std;

void setup_signal_handlers()
{
    signal(SIGINT, sigint_handler);
    signal(SIGTSTP, sigtstp_handler);
}

pid_t foreground_pid = -1;
void sigint_handler(int signo)
{
    if (foreground_pid != -1)
    {
        kill(foreground_pid, SIGINT);
        cout << "Process " << foreground_pid << " interrupted." << endl;
    }
}

void sigtstp_handler(int signo)
{
    if (foreground_pid != -1)
    {
        kill(foreground_pid, SIGTSTP);
        cout << "Process " << foreground_pid << " stopped." << endl;
    }
}

void handle_eof()
{
    cout << "\nExiting shell." << endl;
    exit(0);
}
