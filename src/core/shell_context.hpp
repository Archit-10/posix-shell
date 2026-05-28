#pragma once

#include <string>
#include <vector>

struct ShellContext
{
    std::string cwd;
    std::string oldpwd;
    std::vector<std::string> history;
};