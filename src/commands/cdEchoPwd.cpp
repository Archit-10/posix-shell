#include <iostream>
#include <unistd.h>
#include <cstdlib>

using namespace std;

/*
    CD IMPLEMENTATION (POSIX-style simplified)
*/
bool cd(const string &path)
{
    char old_dir[8192];

    // store current directory before changing
    if (getcwd(old_dir, sizeof(old_dir)) == nullptr)
    {
        perror("getcwd");
        return false;
    }

    const char *target = nullptr;

    if (path.empty() || path == "~")
    {
        target = getenv("HOME");
        if (target == nullptr)
        {
            cerr << "Error: HOME variable not set\n";
            return false;
        }
    }
    else if (path == "-")
    {
        target = getenv("OLDPWD");
        if (target == nullptr)
        {
            cerr << "Error: OLDPWD not set\n";
            return false;
        }
    }
    else if (path == ".")
    {
        return true; // no-op
    }
    else
    {
        target = path.c_str();
    }

    // change directory
    if (chdir(target) != 0)
    {
        perror("chdir");
        return false;
    }

    // update OLDPWD
    setenv("OLDPWD", old_dir, 1);

    return true;
}

/*
    PWD IMPLEMENTATION
*/
void pwd()
{
    char current_directory[8192];

    if (getcwd(current_directory, sizeof(current_directory)) != nullptr)
    {
        cout << current_directory << endl;
    }
    else
    {
        perror("getcwd");
    }
}

/*
    ECHO IMPLEMENTATION
*/
void echo(const string &text)
{
    cout << text << endl;
}