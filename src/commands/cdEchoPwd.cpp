#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <limits.h>

using namespace std;

/* ---------------------------
   CD IMPLEMENTATION
----------------------------*/
bool cd(const string &path)
{
    char current_dir[PATH_MAX];

    // store current directory
    if (getcwd(current_dir, sizeof(current_dir)) == nullptr)
    {
        perror("getcwd");
        return false;
    }

    const char *target = nullptr;
    string resolved_path;

    // ---------------------------
    // CASE 1: empty or "~"
    // ---------------------------
    if (path.empty() || path == "~")
    {
        target = getenv("HOME");
        if (!target)
        {
            cerr << "Error: HOME not set\n";
            return false;
        }
    }

    // ---------------------------
    // CASE 2: previous directory
    // ---------------------------
    else if (path == "-")
    {
        target = getenv("OLDPWD");
        if (!target)
        {
            cerr << "Error: OLDPWD not set\n";
            return false;
        }

        cout << target << endl; // mimic bash behavior
    }

    // ---------------------------
    // CASE 3: absolute path
    // ---------------------------
    else if (path[0] == '/')
    {
        target = path.c_str();
    }

    // ---------------------------
    // CASE 4: relative path
    // ---------------------------
    else
    {
        char temp[PATH_MAX];

        if (getcwd(temp, sizeof(temp)) == nullptr)
        {
            perror("getcwd");
            return false;
        }

        resolved_path = string(temp) + "/" + path;
        target = resolved_path.c_str();
    }

    // ---------------------------
    // CHANGE DIRECTORY
    // ---------------------------
    if (chdir(target) != 0)
    {
        perror("chdir");
        return false;
    }

    // update OLDPWD
    setenv("OLDPWD", current_dir, 1);

    return true;
}

/* ---------------------------
   PWD IMPLEMENTATION
----------------------------*/
void pwd()
{
    char current_directory[PATH_MAX];

    if (getcwd(current_directory, sizeof(current_directory)) != nullptr)
    {
        cout << current_directory << endl;
    }
    else
    {
        perror("getcwd");
    }
}

/* ---------------------------
   ECHO IMPLEMENTATION
----------------------------*/
void echo(const string &text)
{
    cout << text << "\n";
}