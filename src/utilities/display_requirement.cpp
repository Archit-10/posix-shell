#include <iostream>
#include <unistd.h>
#include <limits.h>
#include <cstdlib>
#include "display_requirement.hpp"
using namespace std;

void displayPrompt()
{
    char systemname[HOST_NAME_MAX];
    char username[LOGIN_NAME_MAX];
    char current_directory[PATH_MAX];

    // Get system name
    if (gethostname(systemname, HOST_NAME_MAX) != 0)
    {
        perror("gethostname");
        return;
    }

    // Get username
    if (getlogin_r(username, LOGIN_NAME_MAX) != 0)
    {
        perror("getlogin_r");
        return;
    }

    // Get current directory
    if (getcwd(current_directory, PATH_MAX) == nullptr)
    {
        perror("getcwd");
        return;
    }

    // HOME directory (fix for missing variable)
    const char *home_directory = getenv("HOME");

    string dir_display = current_directory;

    // Replace HOME with ~ if applicable
    if (home_directory != nullptr &&
        dir_display.find(home_directory) == 0)
    {
        dir_display.replace(0, string(home_directory).length(), "~");
    }

    cout << username << "@" << systemname << ":" << dir_display << "> ";
}